# badhub

is Modula's sloppy internal tool to deal with GitHub-isms.

## Purpose

Having a development remote on our
server and trying to get GitHub to
accept `push` requests just kinda sucks,
a lot. This little tool gets around
the issue by letting GitHub have its
own separate history that makes it happy
while the actual *code* is still
correct and up-to-date with our remotes.

## Usage

Make sure you have a rule in your `.gitignore`
for `.ignore/*`

To set your GitHub remote,
run `badhub gh {url}`,
then assuming your
local repo is already set up,
push updates to GitHub
by running `badhub {commit message}`

## Implementation

badhub works by having a clone
off the `github` repo in `.ignore/gh`,
pulling changes to it,
deleting everything inside,
copying over the files in the local repo
over to it,
then running
```
git add .
git commit {commit message}
git push -u github main
```
That's pretty much it. 
It's definitely an inefficient way to do
things, but GitHub is kindof annoying
and I don't feel like slamming my head
into the wall or fixing Microsuck's problems
for them...

por lo: _asi esta suficiente para trabajo
de gobierno_