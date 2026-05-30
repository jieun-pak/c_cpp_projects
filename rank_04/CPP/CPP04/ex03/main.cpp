#include "AMateria.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "ICharacter.hpp"
#include "Character.hpp"
#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"

int main() {
	std::cout << "=== Subject Tests ===" << std::endl;
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter* me = new Character("me");

	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	ICharacter* bob = new Character("bob");

	me->use(0, *bob);
	me->use(1, *bob);

	delete bob;
	delete me;
	delete src;

	std::cout << "\n\n=== Additional Tests ===" << std::endl;

	std::cout << "\n--- Test: Full Inventory ---" << std::endl;
	IMateriaSource* src2 = new MateriaSource();
	src2->learnMateria(new Ice());
	src2->learnMateria(new Cure());

	ICharacter* hero = new Character("hero");

	AMateria* m1 = src2->createMateria("ice");
	AMateria* m2 = src2->createMateria("cure");
	AMateria* m3 = src2->createMateria("ice");
	AMateria* m4 = src2->createMateria("cure");
	AMateria* m5 = src2->createMateria("ice"); // This should not be equipped

	hero->equip(m1);
	hero->equip(m2);
	hero->equip(m3);
	hero->equip(m4);
	hero->equip(m5); // Should not equip (inventory full)

	std::cout << "Using all equipped materias:" << std::endl;
	ICharacter* target = new Character("target");
	hero->use(0, *target);
	hero->use(1, *target);
	hero->use(2, *target);
	hero->use(3, *target);
	hero->use(4, *target); // Should do nothing (out of bounds)

	std::cout << "\n--- Test: Unequip ---" << std::endl;
	AMateria* unequipped = m1; // Save reference before unequip
	hero->unequip(0);
	std::cout << "After unequipping slot 0:" << std::endl;
	hero->use(0, *target); // Should do nothing
	hero->use(1, *target); // Should still work

	// Clean up unequipped materia manually
	delete unequipped;
	delete m5; // This was never equipped

	delete target;
	delete hero;
	delete src2;

	std::cout << "\n--- Test: Deep Copy of Character ---" << std::endl;
	Character original("original");
	AMateria* iceMateria = new Ice();
	original.equip(iceMateria);

	Character copied(original);
	std::cout << "Original character using materia:" << std::endl;
	Character dummy("dummy");
	original.use(0, dummy);
	std::cout << "Copied character using materia:" << std::endl;
	copied.use(0, dummy);

	std::cout << "\n--- Test: Unknown Materia Type ---" << std::endl;
	IMateriaSource* src3 = new MateriaSource();
	src3->learnMateria(new Ice());

	AMateria* unknown = src3->createMateria("fire");
	if (unknown == NULL)
		std::cout << "Unknown materia type 'fire' returns NULL" << std::endl;
	else
		delete unknown;

	delete src3;

	std::cout << "\n=== End of Tests ===" << std::endl;
	return 0;
}
