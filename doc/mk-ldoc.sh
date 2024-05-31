#!/usr/bin/env bash

test -n "$DEBUG" && set -x

#                      __ __       ___
#                     /\ \\ \    /'___`\
#                     \ \ \\ \  /\_\ /\ \
#                      \ \ \\ \_\/_/// /__
#                       \ \__ ,__\ // /_\ \
#                        \/_/\_\_//\______/
#                           \/_/  \/_____/
#                                         Algoritimos
#
#
#      Author: Ivan Lopes
#        Mail: ivan@42algoritmos.com.br
#        Site: http://www.42algoritmos.com.br
#     License: gpl
#       Phone: +1 561 801 7985
#    Language: Shell Script
#        File: mk-ldoc.sh
#        Date: Seg 08 Mai 2017 16:39:42 BRT
# Description:
# ----------------------------------------------------------------------------
# Modo strict
set -euo pipefail
# ----------------------------------------------------------------------------

##############################################################################
##############################################################################
##############################################################################

file=$(echo $* | sed 's/ /-/g' | sed 's/.*/ldoc.&.md/')

# ----------------------------------------------------------------------------

# abrindo descriptor para escrita
exec 4>&1 # stdout duplicado ( FD 4 tem as mesmas caracteristicas
# do STDOUT), aponta para o terminal.
exec 1>$file # stdout aponta para `file'

echo "<!-- prettier-ignore-start -->"
echo
echo $* |
	sed ':a;s/^.\{1,56\}$/ & /;ta; s/.*/&/'
echo ================================================================
echo '                                                              64'
echo "<!-- prettier-ignore-end -->"

echo
echo
echo
echo
echo 'vim: set ts=4 sw=4 tw=64 ft=markdown:'

# fechando descriptor
exec 1>&4 # FD 1 recebe as caracteristicas de FD 4.
# FD 1 ressetado.
exec 4>&- # FD 4 eh liberado.

bash "$HOME/developer/funcoeszz/funcoeszz" zzarrumanome $file

# ----------------------------------------------------------------------------
exit 0
