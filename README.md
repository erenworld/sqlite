# sqlite
SQLite from scratch

# SQLite est divisé en 4 grands modules
1. SQL Compiler – transforme ton SQL en instructions.
2. Core – gère l’exécution des instructions.
3. Backend – lit/écrit dans le fichier .sqlite.
4. Accessories – outils pour le debug, test, etc.


## SQL Compiler
### Tokenizer
Il coupe la requête SQL en petits morceaux appelés tokens.

`sqlite3RunParser(pParse, zSql)`

### Parser
Il vérifie que ta requête est bien écrite.
Ex : il détectera une erreur si tu fais SELCT au lieu de SELECT.
Le parseur est souvent généré automatiquement par un outil (lemon). Il construit un arbre syntaxique.

### Code Generator
Il transforme la requête SQL en instructions pour la machine virtuelle SQLite.

## Core
SQLite exécute les instructions produites.

### SQL Command Processor
Il récupère les instructions générées et les envoie à la machine virtuelle.

### Virtual Machine (VM)
Une machine virtuelle spécifique à SQLite qui lit les instructions une par une et agit en conséquence.
Elle fonctionne comme un petit CPU interne.

`sqlite3VdbeExec()`

Chaque opération comme Column, Gt, ResultRow est codée dans la VM.

## Backend
La VM appelle ce module pour accéder aux données dans le fichier .sqlite.

### B-Tree
Structure utilisée pour organiser les lignes/colonnes dans le fichier.
Optimisé pour les recherches rapides.

### Pager
Gère les pages mémoire (petits blocs de données du fichier).
Évite de tout charger en RAM.

### OS Interface
C’est le lien avec le système d’exploitation (ouvrir fichier, lire, écrire).

## Accessories
Utilities : fonctions utilitaires (ex: affichage de l’arbre d'exécution).
Test Code : sert à tester que tout marche.

> A query goes through a chain of components in order to retrieve or modify data

# Front-end
- tokenizer
- parser
- code generator

The input to the front-end is a SQL query. the output is sqlite virtual machine bytecode (essentially a compiled program that can operate on the database).

# Back-end
- virtual machine
- B-tree
- pager
- os interface

## Le processus
- La machine virtuelle (VM) reçoit des instructions (appelées bytecode) créées à partir de ta requête SQL.
Quand tu fais : SELECT * FROM users;, SQLite traduit ça en instructions internes (comme un petit programme).
Ces instructions sont en bytecode (un langage intermédiaire, plus bas niveau que SQL, mais pas aussi bas que l’assembleur) pur que la VM execute. 
- La VM utilise ces instructions pour travailler sur les tables ou index, qui sont stockés sous forme de B-arbres (B-trees).
- La machine virtuelle est comme un gros switch statement qui dit : “Si l’instruction est Column, je fais ça. Si c’est Next, je fais autre chose.”

```c
switch(opcode) {
  case OP_OpenRead:
    // ouvrir la table
    break;
  case OP_Column:
    // lire une colonne
    break;
  case OP_ResultRow:
    // retourner une ligne
    break;
}
```

- Un B-tree est fait de nœuds (blocs de données), et chaque nœud a la taille d’une page. Une page c'est un petit bloc de données fixe (par défaut : 4096 octets) où chaque nœud du B-tree correspond à une page sur disque.
- Le B-tree demande au pager de lire/écrire des pages sur le disque.
- Le Pager lit/écrit des pages à des endroits précis dans le fichier .sqlite.
- Le fichier SQLite est découpé en pages. Le Pager sait où commencer à lire ou écrire dans ce fichier.
- Le Pager garde en mémoire les pages utilisées récemment et décide quand les enregistrer sur le disque.

 create table users (id int, username varchar(255), email varchar(255));
 .tables
 .exit
