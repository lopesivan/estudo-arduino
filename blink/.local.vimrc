let g:deoplete#sources#clang#flags = ['-I.', '-I/usr/lib/avr/include']
let g:neomake_cpp_clang_args=['-I/usr/lib/avr/include', '-DF_CPU=16000000UL', '-mmcu=atmega328p']

if isdirectory('/usr/lib/avr/include')
    set path+=/usr/lib/avr/include
endif

map <F5> :A<CR>:BufOnly<CR>

let g:surround_{char2nr('c')} = "\\\1command\1{\r}"
map <F9> ysiwc

colorscheme molokai
"" Guimode
if has("gui_running")
  colorscheme molokai
endif


