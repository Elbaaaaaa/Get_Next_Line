## Get Next Line (C)

Implémentation en C de la fonction `get_next_line`, un utilitaire permettant de **lire un fichier (ou un flux) ligne par ligne** à partir d’un descripteur de fichier (`fd`).  
Projet classique orienté **gestion de buffer, allocations, et I/O POSIX**.

### Objectifs

- **Retourner la prochaine ligne** disponible sur un `fd`, sans perdre l’état entre deux appels.
- Gérer des fichiers de taille arbitraire via un **buffer de lecture** (`BUFFER_SIZE`).
- Produire une API simple et réutilisable dans d’autres projets C.

### API

```c
char *get_next_line(int fd);
```

- **Entrée**: `fd` (descripteur de fichier valide).
- **Sortie**:
  - Retourne une **chaîne allouée** correspondant à la prochaine ligne lue.
  - La ligne **inclut le `\n`** si un saut de ligne est rencontré.
  - Retourne `NULL` en cas de fin de fichier ou d’erreur.
- **Mémoire**: la chaîne retournée doit être **libérée par l’appelant** (`free`).

### Configuration (`BUFFER_SIZE`)

`BUFFER_SIZE` contrôle la taille des lectures (`read`).  
Par défaut, la valeur est définie dans `get_next_line.h`, mais tu peux la surcharger à la compilation.

Exemple :

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -c get_next_line.c get_next_line_utils.c
```

### Structure du projet

- `get_next_line.c`: logique principale (lecture, assemblage du “stash”, extraction de ligne).
- `get_next_line_utils.c`: utilitaires (ex: `ft_strlen`, `ft_strjoin`, `ft_strchr`).
- `get_next_line.h`: prototypes et macro `BUFFER_SIZE`.
- `test.txt`: fichier d’exemple pour tests locaux.

### Utilisation (exemple minimal)

```c
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
  int   fd = open("test.txt", O_RDONLY);
  char *line;

  if (fd < 0)
    return (1);
  while ((line = get_next_line(fd)) != NULL)
  {
    printf("%s", line);
    free(line);
  }
  close(fd);
  return (0);
}
```

Compilation :

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
  get_next_line.c get_next_line_utils.c \
  -o gnl_demo
```

### Notes techniques

- **Conservation d’état**: l’implémentation conserve un buffer statique (“stash”) entre les appels à `get_next_line`.
- **I/O**: utilisation de `read(2)` (POSIX) ; fonctionne avec fichiers et, selon l’usage, avec d’autres sources (stdin, pipes).
- **Complexité**: dépend du nombre d’appels `read` et de la stratégie de concaténation (construction progressive de la ligne).

### Auteur

- **ebella** — Étudiant(e) 42  
