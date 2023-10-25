#include <stdlib.h>
#include <stdio.h>
#include <directory.h>
#include <contact.h>
#include <hash.h>

/*
  Crée un nouvel annuaire contenant _len_ listes vides.
*/
struct dir *dir_create(uint32_t len)
{
    dir *directory = malloc(sizeof(dir));
    (directory)->taille = len;
    (directory)->items = calloc(len, sizeof(struct contact *));
    directory->occupation = 0;
    return directory;
}

// Fonction qui redimensionne le directory dans le cas necessaire 
// voir dans delete et insert.
static void resize(struct dir *dir){
  uint32_t len=0;
  if (((dir->occupation)+1)>(0.75)*((dir->taille))){
    len = 2*(dir->taille);
    }
  if ((dir->taille>10) && ((dir->occupation-1)<(0.15*(dir->taille))))
  {
      if ((dir->taille/2)>10)
      {
        len = (dir->taille/2);
      }
      else
      {
        len = 10;
      }
  }
  struct dir *annuaire = dir_create(len);
  annuaire->occupation = dir->occupation;
  for(uint32_t i=0; i<dir->taille; i++)
  {
    struct contact *contact = dir->items[i];
    while (contact!=NULL)
    {
      uint32_t hashage= hash(contact->nom)% (annuaire->taille);
      inserer_debut(&(annuaire->items[hashage]),contact->nom,contact->num);
      contact = contact->suivant;
    }
    free_contact(dir->items[i]);
  }
  free(dir->items);
  dir->items = annuaire->items;
  dir->taille = annuaire->taille;
  free(annuaire);
}  

/*
  Insère un nouveau contact dans l'annuaire _dir_, construit à partir des nom et
  numéro passés en paramètre. Si il existait déjà un contact du même nom, son
  numéro est remplacé et la fonction retourne une copie de l'ancien numéro.
  Sinon, la fonction retourne NULL.
*/

char *dir_insert(struct dir *dir, const char *name, const char *num)
{
    uint32_t hashage= hash(name)% dir->taille;
    if ((chercher(dir->items[hashage],name)== NULL) && ((dir->occupation)+1)>(0.75)*((dir->taille)))
    {
      resize(dir);
    }
    if (chercher(dir->items[hashage],name)== NULL)
    { 
      inserer_debut(&(dir->items[hashage]), name, num);
      (dir->occupation)++;
    }
    else
    {
      char *numero = (char *) chercher(dir->items[hashage],name);
      supprimer_contact(&(dir->items[hashage]),name);
      inserer_debut(&(dir->items[hashage]),name,num);
      return numero;
    }
    return NULL;
}

/*
  Retourne le numéro associé au nom _name_ dans l'annuaire _dir_. Si aucun contact
  ne correspond, retourne NULL.
*/
const char *dir_lookup_num(struct dir *dir, const char *name)
{
    uint32_t hashage= hash(name)% dir->taille;
    return chercher(dir->items[hashage],name);
}

/*
  Supprime le contact de nom _name_ de l'annuaire _dir_. Si aucun contact ne
  correspond, ne fait rien.
*/
void dir_delete(struct dir *dir, const char *name)
{
  uint32_t hashage= hash(name)% dir->taille;
  if ((dir_lookup_num(dir,name)!=NULL) && (dir->taille>10) && ((dir->occupation-1)<(0.15*(dir->taille))))
  {
    resize(dir);
  }
    if (dir_lookup_num(dir,name)!=NULL)
    {
      supprimer_contact(&dir->items[hashage],name);
      (dir->occupation)--;
    }
}

/*
  Libère la mémoire associée à l'annuaire _dir_.
*/
void dir_free(struct dir *dir)
{
    for (uint32_t i=0; i<dir->taille;i++)
    {
      free_contact(dir->items[i]);
    }
    free(dir->items);
    free(dir);
}

/*
  Affiche sur la sortie standard le contenu de l'annuaire _dir_.
*/
void dir_print(struct dir *dir)
{
  for (uint32_t i=0;i<(dir->taille); i++)
  {
    printf("%u--",i);
    affiche_contact(dir->items[i]);
  }
}
