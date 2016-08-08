Feed
====

This module converts markdown documents into an Rss feed
Right now, only `[foo](url)` [link spec] is supported.

Usage
-----

```Python
    obj = mdBookmarks2Rss()
    print obj.main(url=url, authText=authText)
```

[link spec]:http://spec.commonmark.org/0.26/#links