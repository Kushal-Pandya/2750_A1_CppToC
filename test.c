#include "a1.h"


int main(void) {

	struct Class * newClass = createClassList("");
	newClass = addClassToList(newClass, "B");

	printf("%d\n", checkIfClassExists(newClass, "C"));

	displayClassList(newClass);
	
	destroyClassList(newClass);


/*	Class * classes = malloc(sizeof(Class));

	classes->name = malloc(sizeof(char)*5);
	classes->name = "hello";
	
	classes->functions = malloc(sizeof(Var*)*5);
	classes->functions[0] = malloc(sizeof(Var));
	classes->functions[0]->contents = createList("tests");
	classes->functions[0]->contents = addValue(classes->functions[0]->contents, "testing");

	// strcpy(classes->variables[0]->type, "hellw");

	printf("%s\n", classes->name);	

	List * iter;
	for (iter = classes->functions[0]->contents; iter != NULL; iter=iter->next) {
		printf("%s\n", iter->value);
	}

	free(classes);*/

}

