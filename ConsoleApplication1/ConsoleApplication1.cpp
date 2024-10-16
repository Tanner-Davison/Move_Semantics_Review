

#include <iostream>




void process(std::string&& str) {

	// 'str' is an rvalue reference, and we can take ownership of its resources
	std::string localStr = std::move(str);
	// Now, 'localStr' owns the content, and 'str' is left in a valid but unspecified state.
	std::cout << localStr << std::endl;

}

template <typename T>
void howManyTilZero(const T& pVal) {
	T count = pVal;
	T steps = 0.00;
	while (count > 0) {
		std::cout << "Current Count" << count << std::endl;
		count--;
		steps++;
	}
	std::cout << "Completed in " << steps << " steps" << std::endl;
};

class Entity {
public:
	int* member;
	Entity(int size) noexcept : member(new int[size]) {
		if (size > 0) {
			member[0] = 42;
		}
	}

	//move constructor 
	Entity(Entity&& other) noexcept : member(other.member) {
		std::cout << "Move constructor called" << std::endl;
		other.member = nullptr;
	}
	friend std::ostream& operator<<(std::ostream& output, const Entity& obj) {
		output << *obj.member;
		return output;
	}
	~Entity() {
		delete[] member;
	}
	Entity& operator=(Entity&& other)noexcept {
		if (this != &other) {
			delete[] member;
			this->member = other.member;
			other.member = nullptr;
		}
		return *this;
	}
	void toString()const {
		std::cout << "Size of member array: " << *this->member << std::endl;
	}
};

int main() {
	int num = 2;
	howManyTilZero(num);

	Entity entity1(5);
	Entity entity2 = std::move(entity1);
	std::cout << entity2 << std::endl;
	entity1 = std::move(entity2);
	std::cout << entity1 << std::endl;

}

