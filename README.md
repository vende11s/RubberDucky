# Usage:
put payload.ini in same directory, available commands:
* `REM` - To comment
* `STRING` - To some longer text
* `DELAY` - To wait some time (in ms)
* `SHIFTDOWN` - To press shift
* `SHIFTUP` - To unpress shift
* `WINDOWSDOWN` - To press windows key
* `WINDOWSUP` - To unpress windows key
* `ENTER` - To press enter
* `CAPSLOCK` - To press capslock
* `BACKSPACE` - To press backspace, you can too write `BACKSPACE <times>`
* `CTRLDOWN` - To press ctrl
* `CTRLUP` - To unpress ctrl
* `CLIPBOARD` - To copy something to clipboard

You can use just chars (space included) in other lines\
If u want chars like ?!@# u should:  
```
SHIFTDOWN
/
1
2
3
SHIFTUP
```
