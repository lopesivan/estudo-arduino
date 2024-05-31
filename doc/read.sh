#!/usr/bin/env bash
# ----------------------------------------------------------------------------
# Run!
# edit last files

[ -f ~/.fzf.bash ] && source ~/.fzf.bash
_f="/home/linuxbrew/.linuxbrew/opt/bash-it/custom/environment.bash"
[ -f "${_f}" ] && source "${_f}"
dir=$PWD

n=$(
	while read file; do
		head $file |
			sed -n '1,/^=\{64\}/p' |
			sed -e '1d' -e '$d' |
			~/.linuxbrew/bin/sed.joinlines |
			sed 's/  */ /g' |
			sed 's/^/\t/'
	done < <(find ${dir}/ -type f -name ldoc.\*.md | sort) |
		nl -s: |
		fzf --height 100% --layout=reverse |
		cut -d: -f1
)

file=$(
	find ${dir}/ -type f -name ldoc.\*.md |
		sort |
		sed -n "${n}{p;q}"
)

nvim -R -c'0' -c'map ? :qall!<CR>' -c'map <ESC> :qall!<CR>' -c'map q :qall!<CR>' $file

exit 0
