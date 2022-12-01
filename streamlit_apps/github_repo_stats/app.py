import streamlit as st
import random
import requests

SAMPLE_REPOS = [
    "wandb/wandb",
    "wandb/local",
    "pytorch/pytorch",
    "keras-team/keras",
    "tensorflow/tensorflow",
    "duckdb/duckdb",
    "minio/minio",
    "neithere/argh",
]

def main(st):
    all_data = []
    all_errs = []
    with st.container():
        repo_names = st.text_input("repo_names")
        if repo_names == "":
            samples = sample_repos()
            default_input = ",".join(samples)
            st.write("using sample input: ", default_input)
            repo_names = default_input
        for i,name in enumerate(repo_names.split(",")):
            repo_data, err = crawl_repo(name)
            st.line_chart(repo_data, x="created_at", y=("issue_count","release_count"))
            all_data.extend(repo_data)
            all_errs.append(err)
    with st.expander("Debug"):
        st.text("errors:")
        st.json(all_errs)
        st.text("data:")
        st.dataframe(all_data)


@st.cache(ttl=600)
def sample_repos():
    return random.sample(SAMPLE_REPOS, 3)


@st.cache(ttl=600)
def crawl_repo(repo_name):

    print(f"making requests for {repo_name}")
    issues = requests.get(f"https://api.github.com/repos/{repo_name}/issues?filter=all&state=all&sort=created")
    releases = requests.get(f"https://api.github.com/repos/{repo_name}/releases")

    if not issues or not releases:
        err = f"error in issues or releases request:\n{issues.text}\n{releases.text}"
        data = [dict(repo_name=repo_name, created_at=None, issue_count=None, release_count=None, url=None)]
        print(err)
        return data, err

    all_data = []

    for row in issues.json():
        # print(f"row: {row}")
        created_at, url = row.get("created_at"), row.get("html_url")
        all_data.append((created_at, 1, 0, url))

    for row in releases.json():
        # print(f"row: {row}")
        created_at, url = row.get("created_at"), row.get("html_url")
        all_data.append((created_at, 0, 1, url))
    
    all_data.sort(key=lambda row: row[0])

    processed_data = []
    issue_count = 0
    release_count = 0
    for created_at, issue_incr, release_incr, url in all_data:
        issue_count += issue_incr
        release_count += release_incr
        processed_data.append(dict(
            repo_name=repo_name,
            created_at=created_at,
            issue_count=issue_count,
            release_count=release_count,
            url=url
        ))

    return processed_data, None

main(st)

