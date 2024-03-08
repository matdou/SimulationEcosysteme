## Environment Setup for macOS

Ensure your shell is zsh before proceeding. Run `bash echo $SHELL` in your terminal. If the output is `/bin/zsh`, you're using zsh.

### Update zsh Configuration

Edit .zshrc: Open with `open -a TextEdit ~/.zshrc`.

### Add Variables:
```sh
export CPATH=/opt/X11/include:$CPATH
export LIBRARY_PATH=/opt/X11/lib:$LIBRARY_PATH
export DYLD_LIBRARY_PATH=/opt/X11/lib:$DYLD_LIBRARY_PATH
```

### Apply Changes:
Run `source ~/.zshrc` in your terminal.

This setup ensures the X11 headers and libraries are correctly recognized for development.
