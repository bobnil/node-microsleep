{
  "targets": [{
    "target_name": "sleep",
    "sources": ["src/sleep.cc"],
    "include_dirs": [
      "<!(node -e \"require('nan')\")"
    ],
    "cflags": ["-std=c++11"]
  }]
}
