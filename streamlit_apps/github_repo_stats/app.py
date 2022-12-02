import streamlit as st
import random
import requests
import datetime as dt

SAMPLE_REPOS = [
    "wandb/local",
    "pytorch/pytorch",
    "keras-team/keras",
    "tensorflow/tensorflow",
    "duckdb/duckdb",
    "minio/minio",
    "neithere/argh",
]

CACHE_TIME = 86400

def parse(strtime):
    return dt.datetime.strptime(strtime, "%Y-%m-%dT%H:%M:%SZ")

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
            st.markdown(f"**{name}**")
            st.line_chart(repo_data, x="created_at", y=("issue_count","release_count"))
            all_data.extend(repo_data)
            all_errs.append(err)
    with st.expander("Debug"):
        st.text("errors:")
        st.json(all_errs)
        st.text("data:")
        st.dataframe(all_data)

        st.text("rate limit:")
        st.json(get_rate_limit())

@st.cache(ttl=60)
def sample_repos():
    return random.sample(SAMPLE_REPOS, 3)

@st.cache(ttl=60)
def get_rate_limit():
    resp = requests.get(f"https://api.github.com/rate_limit")
    obj = resp.json()
    parse_unixtimestamp(obj)
    return obj

def parse_unixtimestamp(obj, key="reset", depth=10):
    if depth <= 0:
        return
    if key in obj:
        relative = dt.datetime.fromtimestamp(obj[key]) - dt.datetime.now()
        obj[key+"_parsed"] = str(relative)
    for k,v in obj.items():
        if isinstance(v, dict):
            parse_unixtimestamp(v, key=key, depth=depth-1)

@st.cache(ttl=CACHE_TIME)
def get_request(req_str):
    resp = requests.get(req_str)
    return resp

def page_and_parse(gh_api_request):
    data = []
    for page_idx in range(100):
        resp = get_request(gh_api_request + f"&per_page=100&page={page_idx+1}")
        if not resp:
            err = f"error in making request: {resp.text}"
            return data, err
        rc = 0
        for row in resp.json():
            rc += 1
            created_at, url = row.get("created_at"), row.get("html_url")
            data.append((created_at, url))
        if rc < 100:
            break
    return data, None


def crawl_repo(repo_name):

    print(f"making requests for {repo_name}")

    releases, releases_err = page_and_parse(f"https://api.github.com/repos/{repo_name}/releases")
    issues, issues_err = page_and_parse(f"https://api.github.com/repos/{repo_name}/issues?filter=all&state=all&sort=created")

    all_data = []
    for created_at, url in issues:
        all_data.append((created_at, 1, 0, url))
    for created_at, url in releases:
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
            created_at=parse(created_at),
            issue_count=issue_count,
            release_count=release_count,
            url=url
        ))
    if len(processed_data) == 0:
        processed_data.append(dict(
            repo_name=repo_name,
            created_at=parse("2222-12-12T22:22:22Z"),
            issue_count=0,
            release_count=0,
            url=""
        ))

    return processed_data, issues_err or releases_err


main(st)



