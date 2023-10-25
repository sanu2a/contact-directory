#ifndef _CONTACT_H_
#define _CONTACT_H_

/*
  Un contact représente une association {nom, numéro}
  Ainsi qu'un pointeur vers le contact suivant.
*/
struct contact{
  const char *nom;
  const char *num;
  struct contact *suivant;
};
extern void affiche_contact(struct contact *annuaire);
extern void inserer_debut(struct contact **annuaire, const char *nom, const char *num);
extern void supprimer_contact(struct contact **annuaire,const char *nom);
extern const char *chercher(struct contact *annuaire,const char *nom);
extern void free_contact(struct contact * annuaire);
#endif /* _CONTACT_H_ */
