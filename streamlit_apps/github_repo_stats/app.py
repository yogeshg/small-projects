import streamlit as st
import random

SAMPLE_REPOS = [
    "wandb/wandb",
    "wandb/local",
    "pytorch",
    "keras",
    "tensorflow",
    "flask",
    "duckdb",
    "minio",
    "neithere/argh",
]

def main(st):
    data = []
    with st.container():
        repo_names = st.text_input("repo_names")
        if repo_names == "":
            samples = sample_repos()
            default_input = ",".join([d.get("package") for d in samples])
            st.write("using sample input: ", default_input)
            repo_names = default_input
        all_data = []
        for i,name in enumerate(repo_names.split(",")):
            repo_data = crawl_repo(name)
            st.line_chart(repo_data, x="created_at", y=("issue_count","release_count"))
            all_data.extend(repo_data)
    with st.expander("Debug"):
        st.dataframe(data)


@st.cache(ttl=10)
def sample_repos():
    return random.sample(SAMPLE_REPOS, 10)


@st.cache(ttl=10)
def crawl_repo(repo_name):

    issues = requests.get(f"https://api.github.com/repos/{repo_name}/issues?filter=all&state=all&sort=created")
    releases = requests.get(f"https://api.github.com/repos/{repo_name}/releases")

    all_data = []

    for row in issues.json():
        created_at, url = row.get("created_at"), row.get("html_url")
        all_data.append(created_at, 1, 0, url)

    for row in releases.json():
        created_at, url = row.get("created_at"), row.get("html_url")
        all_data.append(created_at, 0, 1, url)
    
    all_data.sort(lambda row: row.get("created_at"))

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

    return processed_data

main(st)

