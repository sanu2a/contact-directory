#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <contact.h>


/* affiche les contacts contenu dans la liste des contacts avec leur numero */
void affiche_contact(struct contact *annuaire)
{   
    printf("{");
    while (annuaire!= NULL)
    {
        printf("Le numero de %s est %s,", (annuaire->nom), (annuaire->num));
        annuaire = annuaire->suivant;
    }
    printf("}\n");
}
/* insere un contact au debut de la liste des contacts */
void inserer_debut(struct contact **annuaire, const char *nom, const char *num)
{
    struct contact *nouveau =malloc(sizeof( struct contact));
    (nouveau->nom) = nom;
    (nouveau->num) = num;
    (nouveau->suivant) = *annuaire; 
    (*annuaire) = nouveau;
}
/* supprime un contact si il existe dans la liste des contacts, sinon on ne fait rien */
void supprimer_contact(struct contact **annuaire,const char *nom)
{  
    struct contact sentinelle = { "thala", "", (*annuaire)};
    struct contact *parcours = &sentinelle;
    while (parcours->suivant != NULL && parcours->suivant->nom != nom)
    {
        parcours = parcours->suivant;
    }
    if (parcours->suivant != NULL)
    {
        struct contact *libre = parcours->suivant;
        parcours->suivant = libre->suivant;
        free(libre);
    }
    (*annuaire) = sentinelle.suivant;
}
/*cherche un contact a partir de son nom dans la liste des contacts 
     renvoie son numero si il existe, sinon return null*/
const char *chercher(struct contact *annuaire,const char *nom)
{
    while ((annuaire)!= NULL)
    {
        if (annuaire->nom == nom)
        {
            return (annuaire->num);
        }
        annuaire = annuaire->suivant;
    }
    return NULL;
}
/* libere la memoire associé a la liste des contacts*/
void free_contact(struct contact * annuaire)
{
    while (annuaire!=NULL)
    {   
        struct contact *prec= annuaire->suivant;
        free(annuaire);
        annuaire= prec;
    }  
}