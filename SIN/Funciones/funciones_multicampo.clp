(length$(create$ hola mundo))

(nth$ 3 (create$ huevos pan leche azucar))

(member$ pan (create$ huevos pan leche azucar))

(subsetp (create$ leche) (create$ huevos pan leche azucar))

(subseq$ (create$ huevos pan leche azucar mayonesa) 2 4)

(first$ (create$ huevos pan leche azucar))

(rest$ (create$ huevos pan leche azucar))

(explode$ "hola mundo")

(implode$ (create$ huevos pan leche azucar))

(insert$ (create$ 1 3 7) 2 2)

(delete$ (create$ 1 2 3 4 5 6) 2 4)