set makeprg=ninja

let g:neomake_build_maker = { 'exe': &makeprg, 'args': ['-C', 'build'] }
nmap <silent> <leader>B :Neomake! build<CR>
