

def merge_sort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2  # Find the middle index

        # Divide the array into two halves
        left_half = arr[:mid]
        right_half = arr[mid:]

        # Recursive call on each half
        merge_sort(left_half)
        merge_sort(right_half)

        # Merge the two sorted halves
        i = j = k = 0

        while i < len(left_half) and j < len(right_half):
            if left_half[i].get_strength() < right_half[j].get_strength():
                arr[k] = left_half[i]
                i += 1
            elif left_half[i].get_strength() > right_half[j].get_strength():
                arr[k] = right_half[j]
                j += 1
            else:
                if left_half[i].get_age() > right_half[j].get_age():
                    arr[k] = left_half[i]
                    i += 1
                else:
                    arr[k] = right_half[j]
                    j += 1
            k += 1

        # Checking if any element was left
        while i < len(left_half):
            arr[k] = left_half[i]
            i += 1
            k += 1

        while j < len(right_half):
            arr[k] = right_half[j]
            j += 1
            k += 1