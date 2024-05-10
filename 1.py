class Data:
    def __init__(self, client_id=None, telephone=None):
        self.client_id = client_id
        self.telephone = telephone

class Hashmap:
    def __init__(self, size):
        self.size = size
        self.table = [Data() for _ in range(size)]

    def insert(self, client_id, telephone):
        index = client_id % self.size
        while self.table[index].client_id is not None:
            index = (index + 1) % self.size
        self.table[index] = Data(client_id, telephone)

    def search(self, client_id):
        index = client_id % self.size
        original_index = index
        while self.table[index].client_id is not None:
            if self.table[index].client_id == client_id:
                return self.table[index].telephone
            index = (index + 1) % self.size
            if index == original_index:
                break
        return None

    def delete(self, client_id):
        index = client_id % self.size
        original_index = index
        while self.table[index].client_id is not None:
            if self.table[index].client_id == client_id:
                self.table[index] = Data()
                return
            index = (index + 1) % self.size
            if index == original_index:
                break

if __name__ == '__main__':
    database = Hashmap(10)
    while True:
        print("************* MENU *************")
        print("1. Insert Client Details")
        print("2. Search Client Details")
        print("3. Delete Client Details")
        print("4. Exit")
        choice = input("Enter your choice: ")
        if choice == '1':
            client_id = int(input("Enter client ID: "))
            telephone = int(input("Enter telephone number: "))
            database.insert(client_id, telephone)
            print("Client details inserted successfully.")
        elif choice == '2':
            client_id = int(input("Enter client ID: "))
            telephone = database.search(client_id)
            if telephone is not None:
                print("Telephone Number:", telephone)
            else:
                print("Client not found.")
        elif choice == '3':
            client_id = int(input("Enter client ID: "))
            database.delete(client_id)
            print("Client details deleted successfully.")
        elif choice == '4':
            print("Exiting...")
            break
        else:
            print("Invalid choice. Please try again.")
