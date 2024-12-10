# Raekan

A thing.

## Quick, fast, in a hurry

1. Clone
2. Ensure wXwidgets is installed: `vcpkg install wxwidgets`
3. Configure: `cmake -S . -B build`
4. Build: `cmake --build build`

## Or - with [just](https://github.com/casey/just) installed

Steps (1) & (2) above, then:
`just c && just b` to configure and build it (in debug config).

`just --list` or `just --choose` will list a summary of available
recipes or present an interactive chooser, respectively. Note the
latter requires [fzf](https://github.com/junegunn/fzf) or something
like it.

---
# TODO

* [ ] Config manager
* [ ] Sort out having 'Main' notebook pane hidden/disabled at startup
    - Something's wrong atm: pagecounts showing random bits
- [ ] Start HTML stuff
  - [ ] File loader
  - [ ] Preview pane (scrollable-derived)

## Landing

Need to decide how to handle an extant site, and what I should implement first.

  - [ ] Site loader (from DB file)
  - [ ] Info boxes for if stuff was found (css/scss, templates dir, etc) at chosen site root
        _Started_

## DB

Text-only, to start.

  * [ ] Suss out serialising a bare HTML/CSS-only site dir
  * [ ] Start a DB handler class
