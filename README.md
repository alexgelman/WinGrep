# WinGrep
A simple Windows utility to search for strings in Windows files.

## WinGrep Usage
```
WinGrep.exe --paths=(Paths to search) --search=(Exact string to search) [--maxsize=(Max file size in bytes to search in)]

  --help                Produce help message.
  --paths arg           Space separated paths to search in.
  --search arg          Exact string to search in files.
  --maxsize arg (=-1)   The maximum file size in bytes to search in. Enter -1 
                        to search all files.
  --unicode             Output in Unicode.
  --debug               Print debug information.
```

## Dependencies
WinGrep depends on [boost](http://www.boost.org/) v1.59 program options and filesystem libraries.
You'll have to download and compile it yourself.

## License
WinGrep is released under the [MIT license](https://opensource.org/licenses/MIT)
