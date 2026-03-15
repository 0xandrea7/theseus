# Theseus

Un visualizzatore e risolutore di labirinti da riga di comando scritto in C puro. 
Il programma e' basato su una struttura dati a **Stack** per esplorare i percorsi, e applica il **Backtracking** per scartare in tempo reale i vicoli ciechi.

![Demo](teseo_demo.mp4)

## Compilazione ed Esecuzione

```bash
$gcc main.c -o theseus$ ./theseus maps/hard
