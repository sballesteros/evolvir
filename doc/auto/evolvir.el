(TeX-add-style-hook "evolvir"
 (lambda ()
    (LaTeX-add-bibliographies
     "/home/seb/Documents/biblio_bibtex/biblio_seb")
    (LaTeX-add-labels
     "fig:selecao"
     "fig:parametres"
     "fig:evolvir"
     "fig:parametres_mutant"
     "fig:mutant"
     "fig:compromis")
    (TeX-run-style-hooks
     "natbib"
     "tikz"
     "pgf"
     "mathrsfs"
     "amssymb"
     "amsmath"
     "caption"
     "float"
     "graphicx"
     "multirow"
     "array"
     "babel"
     "french"
     "inputenc"
     "utf8"
     "geometry"
     "latex2e"
     "art12"
     "article"
     "12pt")))

