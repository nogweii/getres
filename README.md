# getres
This is a *very* simple program, but it's fun so I did it.

## About: The History

Following the philosophy of "Do one thing well" this gets values from the
resource manager you have running on your Linux system. (Or any another system
that runs X11.) That's it. Nothing more, nothing less. Really useful for things
like scripting. And it's in C, so it's really fast!

### Rationale for this beast

Dzen. Really. It's an awesome program, and I have tons of scripts using it, but
their colors are all mixed together. No consistency. Now, I could patch dzen,
and it would be nice, but that's more work than this. And I probably won't learn
as much!

So instead of editing each shell script to sync the colors, why not just have
the theming information stored in a central location? And I already do that with
(a bit) in Xdefaults, so why not manage dzen colors via Xdefaults? I don't know
how to properly call `xrdb` so this seems like a perfectly reasonable supplement
to it.

### Usage is very 'complex'

You use it by passing the application name and the resource. For instance, if
you had the following in your `~/.Xdefaults`:

    urxvt*background: black

You could retrieve the value ('black') by calling getres as such:

    getres urxvt background

And that's it!

## Installation -- simple!

* Compile it via `make`
* Install it by copying it to somewhere in `$PATH`

## Limitations (But they aren't, really)

* Due to the use of XGetDefault, getres can not get any further than 1 level
  deep in the resource manager. So deeply nested values such as
  'xcalc.Button.Color' will not work.
* It's case sensitive, so "Urxvt" is not the same as "urxvt"

## Copyright...or what's left of it.

Licensed under the MIT/X11, see the source code 'main.c' for a copy of the
terms.
