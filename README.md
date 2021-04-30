# About this fork

## Warning

My changes to dwm is in a different branch, with the `suckless` branch containing the updated upstream code.

Whenever I pull the updates from suckless.org, I rebase my changes onto the `suckless` branch. So my commits always stays on top of the upstream code. However, the commits will be modified (new commit hash) every time I update, which could be quite annoying if anyone including me want to keep track on a specific commit.

I *will force push* until either I found out a better way to maintain the different patches or, not quite possibly, anyone else wants to fork and contribute to my patched dwm.

![](https://github.com/OliverLew/oliverlew.github.io/blob/pictures/dwm.png?raw=true)

## Patches

You can check the first few dozens of commits in the git repo for the patches I made.

Something worth mentioning:

### A UNIVERSAL, layout-independent gaps patch.

That is, you don't have to change any layouts to make them show window gaps!

Kinda hacky (not that much). I did two things to produce gaps between windows and window-monitor:

1. Adding a margin around every tiled window.
2. Adding a padding to the whole monitor area.

The step 1 will almost finish the job, but the gap between windows will be 2 times the margin, while the outer gap between window and monitor bezel will only be equal to the margin, only half of the former. Thus in the step 2, I added a padding, equal to the margin, to the monitor, which effectively made the outer gap also 2 times the margin.

But, I think it is in someway better than to modify EVERY layout patch.

### Status bar patches

#### Clickable status bar

This is based on the [statuscmd patch](https://dwm.suckless.org/patches/statuscmd/)

You can add `\000` to `\017` in the `xsetroot` command to specify clickable areas.

Once you click on one area *following* `\0NN`, the script `statuscmd` will be called with hex value of `NN` as the first argument.

E.g. If you
```sh
xsetroot -name " a $(printf "\001") b "
```
Then, Status bar shows ` a  b `. Click on ` b ` with left button, then dwm will execute the command `BUTTON=1 <statuscmd_script> 1`.

#### Base-8 color on status bar

This is based on the [statuscolors patch](https://dwm.suckless.org/patches/statuscolors/)

You can add `\020` to `\037` in the `xsetroot` command to specify different colors:

- `\020` to `\027` specifies foreground color (color 8 to color 15, normally they are bright variants)
- `\030` to `\037` specifies background color (color 0 to color 7)

E.g. If you
```sh
xsetroot -name " a $(printf "\021\033") b "
```
Status bar shows ` a  b `, with ` b ` in red color and yellow background.

### Other patches:

These are the patches I applies with few or no modifications:

- Toggle fullscreen with [actualfullscreen](https://dwm.suckless.org/patches/actualfullscreen/)
- [Center](https://dwm.suckless.org/patches/center/) and [sticky](https://dwm.suckless.org/patches/actualfullscreen/) rules
- [Per-tag](https://dwm.suckless.org/patches/pertag/) patch
- [Focus on click](https://dwm.suckless.org/patches/focusonclick/), instead of on hover
- [Resize windows at all corners](https://dwm.suckless.org/patches/resizecorners/), I also made the resize cursor different accordingly
- Navigation abilities, e.g. shift tags (similar to [nextprev](https://dwm.suckless.org/patches/nextprev/)), cycle layouts (similar to [cyclelayouts](https://dwm.suckless.org/patches/cyclelayouts/)), [move windows](https://dwm.suckless.org/patches/push/)
- [Focus on netactive](https://dwm.suckless.org/patches/focusonnetactive/). Rofi's window switching won't work otherwise
- Fixborders patch under [alpha](https://dwm.suckless.org/patches/alpha/), which fixes the transparent border under compositors
- [Restart with SIGHUP](https://dwm.suckless.org/patches/restartsig/) signal
- [Xresources](https://dwm.suckless.org/patches/xrdb/) patch
- [Systray](https://dwm.suckless.org/patches/systray/) patch

## Key/mouse bindings

- Only window manger related keybindings are in `config.h` file, like tag/client management.
- Other window manager independent key bindings (such as application launching) are in `sxhkd` configuration in my dotfiles repo.
- Mouse binding on status bar is dealt with `dwm-status` script in my dotfiles repo.
