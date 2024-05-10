class Node:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.next = None

class HashTable:
    def __init__(self, size, replacement=False):
        self.size = size
        self.table = [None] * size
        self.replacement = replacement

    def hash_function(self, key):
        return hash(key) % self.size

    def insert(self, key, value):
        index = self.hash_function(key)
        if self.table[index] is None:
            self.table[index] = Node(key, value)
        else:
            if self.replacement:
                # Replace existing value if key already exists
                current = self.table[index]
                while current:
                    if current.key == key:
                        current.value = value
                        return
                    if current.next is None:
                        break
                    current = current.next
                current.next = Node(key, value)
            else:
                # Chaining without replacement
                current = self.table[index]
                while current.next:
                    current = current.next
                current.next = Node(key, value)

    def find(self, key):
        index = self.hash_function(key)
        current = self.table[index]
        while current:
            if current.key == key:
                return current.value
            current = current.next
        return None

    def delete(self, key):
        index = self.hash_function(key)
        current = self.table[index]
        prev = None
        while current:
            if current.key == key:
                if prev:
                    prev.next = current.next
                else:
                    self.table[index] = current.next
                return
            prev = current
            current = current.next

    def display(self):
        for index in range(self.size):
            current = self.table[index]
            while current:
                print(f"({current.key}, {current.value})", end=" -> ")
                current = current.next
            print("None")

# Example usage:
size = int(input("Enter size of hash table: "))
replacement = input("Do you want to use replacement (yes/no): ").lower() == "yes"

dictionary = HashTable(size, replacement)

while True:
    print("\n1. Insert")
    print("2. Search")
    print("3. Delete")
    print("4. Display")
    print("5. Exit")

    choice = int(input("Enter your choice: "))

    if choice == 1:
        key = input("Enter key: ")
        value = input("Enter value: ")
        dictionary.insert(key, value)
    elif choice == 2:
        key = input("Enter key to search: ")
        value = dictionary.find(key)
        if value is not None:
            print(f"Value found: {value}")
        else:
            print("Key not found")
    elif choice == 3:
        key = input("Enter key to delete: ")
        dictionary.delete(key)
        print("Key deleted successfully")
    elif choice == 4:
        print("Displaying dictionary:")
        dictionary.display()
    elif choice == 5:
        print("Exiting...")
        break
    else:
        print("Invalid choice")
