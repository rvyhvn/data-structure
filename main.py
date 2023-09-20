import random
 
# Fungsi untuk mencetak list angka acak
def print_random_list():
    random_list = [random.randint(1, 100) for _ in range(100)]
    print("List Angka Acak:")
    print(random_list)
 
# Fungsi untuk mencetak list angka yang hampir terurut
def print_nearly_sorted_list():
    nearly_sorted_list = [i for i in range(1, 101)]
    # Mengacak beberapa elemen untuk membuatnya hampir terurut
    for _ in range(30):
        idx1, idx2 = random.randint(0, 99), random.randint(0, 99)
        nearly_sorted_list[idx1], nearly_sorted_list[idx2] = nearly_sorted_list[idx2], nearly_sorted_list[idx1]
    print("List Angka Hampir Terurut:")
    print(nearly_sorted_list)
 
# Fungsi untuk mencetak list angka terbalik
def print_reversed_list():
    reversed_list = [i for i in range(100, 0, -1)]
    print("List Angka Terbalik:")
    print(reversed_list)
 
# Panggil fungsi-fungsi untuk mencetak list
print_random_list()
print("\n")
print_nearly_sorted_list()
print("\n")
print_reversed_list()
