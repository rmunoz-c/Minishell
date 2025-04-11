#!/bin/bash

SESSION="my_session"

# Crea la sesión y el primer panel (izquierda)
tmux new-session -d -s "$SESSION" 'bash'

# Divide horizontalmente (crea el derecho)
tmux split-window -h

# En el panel derecho, ejecuta make y luego ./minishell
tmux send-keys -t "$SESSION":0.1 'clear && make && ./minishell' C-m

# En el panel izquierdo, limpia la pantalla
tmux send-keys -t "$SESSION":0.0 'clear' C-m

# Activa la sincronización entre paneles
tmux setw -t "$SESSION":0 synchronize-panes on

# Adjunta la sesión
tmux attach-session -t "$SESSION"
