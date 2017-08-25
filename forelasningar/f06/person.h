struct person;

/** mk_person
 *
 *  @arg first The first name of the person
 *  @arg last  The last name of the person
 *
 *  @returns A person named "first last", or NULL if a person
 *  could not be created
 */
struct person *mk_person(char *first, char *last);

/** get_first_name
 *
 *  @arg p A person
 *
 *  @returns The first name of p
 */
char *get_first_name(struct person *p);

/** get_last_name
 *
 *  @arg p A person
 *
 *  @returns The last name of p
 */
char *get_last_name(struct person *p);