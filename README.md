## Necosay

#### Install to `/usr/local/bin`

```
sh install.sh
```

#### Examples:

```sh
necosay $ cat test.txt | necosay 
===============================================================================
|   * whitespace=trail,space                                                  |
|   *.[ch] whitespace=indent,trail,space,incomplete diff=cpp                  |
|   *.sh whitespace=indent,trail,space,incomplete text eol=lf                 |
|   *.perl text eol=lf diff=perl                                              |
|   *.pl text eof=lf diff=perl                                                |
|   *.pm text eol=lf diff=perl                                                |
|   *.py text eol=lf diff=python                                              |
|   *.bat text eol=crlf                                                       |
|   CODE_OF_CONDUCT.md -whitespace                                            |
|   /Documentation/**/*.adoc text eol=lf whitespace=trail,space,incomplete    |
|   /command-list.txt text eol=lf                                             |
|   /GIT-VERSION-GEN text eol=lf                                              |
|   /mergetools/* text eol=lf                                                 |
|   /t/oid-info/* text eol=lf                                                 |
|   /Documentation/git-merge.adoc conflict-marker-size=32                     |
|   /Documentation/git-merge-file.adoc conflict-marker-size=32                |
|   /Documentation/gitk.adoc conflict-marker-size=32                          |
|   /Documentation/user-manual.adoc conflict-marker-size=32                   |
|   /t/t????-*.sh conflict-marker-size=32                                     |
===============================================================================
                        o
                       o
                     o
        /\      /\
      -/--\----/--\-
     /  /\      /\  \
    /  (())    (())  \
    \   \/      \/   /
     \    (_/\_)    /
      --------------
```

```sh
necosay $ necosay "foo bar"
===============
|   foo bar   |
===============
  o
   o
     o
        /\      /\
      -/--\----/--\-
     /  /\      /\  \
    /  (())    (())  \
    \   \/      \/   /
     \    (_/\_)    /
      --------------
```

#### Build

```sh
sh build.sh
```

#### Uninstall
```
sh uninstall.sh
```

#### Details
`Necosay` will translate all the tabs into 4 spaces. This is crutial for alignment, and I don't really care what you think about this.
