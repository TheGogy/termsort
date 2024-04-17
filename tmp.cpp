/**
Beeg program with lots of sorting algorithms
Sorting algorithms included:

Sorting algorithm       || Difficulty || Speed
-------------------------------------------------
‣ Quick sort [34]       ||     4      ||  10
‣ Bubble sort [58]      ||     2      ||  1
‣ Shell sort [74]       ||     3      ||  7
‣ Merge sort [88]       ||     7      ||  9
‣ Tree sort [132]       ||     10     ||  8
‣ Heap sort [180]       ||     5      ||  7
‣ Pancake sort [214]    ||     7      ||  2
‣ Gnome sort [245]      ||     1      ||  2

sorry if the file is a little messy!
I originally made it just for quicksort but just kept adding sorters

Have fun! c:

**/

#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <limits>

#include <chrono>
using namespace std::chrono;
using namespace std;

// Partition the vector around the pivot and return the index of the pivot
int partition(vector<int>& arr, int left, int right) {
    int pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i+1], arr[right]);
    return i+1;
}

// Quicksort function
void quicksort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int pivot = partition(arr, left, right);
        quicksort(arr, left, pivot-1);
        quicksort(arr, pivot+1, right);
    }
}

void bubblesort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        bool swapped = false;
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void shellsort(vector<int>& arr) {
    int n = arr.size();
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j-gap] > temp; j -= gap) {
                arr[j] = arr[j-gap];
            }
            arr[j] = temp;
        }
    }
}

void merge(vector<int>& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;
    vector<int> L(n1), R(n2);

    // Create subarrays of left and right
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[middle + 1 + j];
    }

    // Merge the temporary subarrays back into arr
    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i++];
        }
        else {
            arr[k] = R[j++];
        }
        k++;
    }
    while (i < n1) {
        arr[k++] = L[i++];

    }
    while (j < n2) {
        arr[k++] = R[j++];
    }
}

void mergesort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergesort(arr, left, middle);
        mergesort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

// Tree sort because trees
class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int data) {
        this->data = data;
        left = right = nullptr;
    }
};

Node* insert(Node* node, int data) {
    // If the tree is empty, create a new node
    if (node == nullptr) {
        return new Node(data);
    }
    if (data < node->data) {
        node->left = insert(node->left, data);
    }
    else if (data > node->data) {
        node->right = insert(node->right, data);
    }

    return node;
}

// Traverse the binary search tree in order and append each node's data to the output vector
void inorderTraversal(Node* node, vector<int>& output) {
    if (node != nullptr) {
        inorderTraversal(node->left, output);
        output.push_back(node->data);
        inorderTraversal(node->right, output);
    }
}

// Tree sort function
void treesort(vector<int>& arr) {
    Node* root = nullptr;
    for (int x : arr) {
        root = insert(root, x);
    }
    arr.clear();
    inorderTraversal(root, arr);
}

// Heap sort stuff
void heapify(vector<int>& arr, int N, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < N && arr[l] > arr[largest]) {
        largest = l;
    }

    if (r < N && arr[r] > arr[largest]) {
        largest = r;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, N, largest);
    }
}

void heapsort(vector<int>& arr, int N) {
    for (int i = N / 2 - 1; i >= 0; i--) {
        heapify(arr, N, i);
    }
    for (int i = N - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Pancake sort! ^u^
// This one is really cool because it uses a very weird method
// of rearranging the elements. The only operation it uses to
// arrange stuff is by "flipping" (reversing) the array from 0
// to i.
void flip(vector<int>& arr, int i) {
    int temp, start = 0;
    while (start < i) {
        temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;
        start++;
        i--;
    }
}

int findMax(vector<int>& arr, int n) {
    int max, i;
    for (max = 0, i = 0; i < n; ++i) {
        if (arr[i] > arr[max]) {
            max = i;
        }
    }
    return max;
}

void pancakesort(vector<int>& arr, int n) {
    for (int cur_size = n; cur_size > 1; --cur_size) {
        int max = findMax(arr, cur_size);
        if (max != cur_size-1) {
            flip(arr, max);
            flip(arr, cur_size-1);
        }
    }
}

void gnomesort(vector<int>&  arr, int n) {
    int index = 0;
    while (index < n) {
        if (index == 0)
            index++;
        if (arr[index] >= arr[index - 1])
            index++;
        else {
            swap(arr[index], arr[index - 1]);
            index--;
        }
    }
    return;
}


void shuffle(vector<int>& arr) {
    random_device rd; // Get random seed
    mt19937 gen(rd()); // Mersenne Twister random number generator p3p
    for (int i = arr.size()-1; i > 0; i--) {
        uniform_int_distribution<int> dist(0, i);
        int j = dist(gen);
        swap(arr[i], arr[j]);
    }
}

// Test the quicksort function
int main() {

    srand(time(NULL));
    int n;
    bool verbose;
    bool use_slow_sorters; // Some algorithms take their time (and that's okie! ^u^)
                           // But sometimes we want to go fast.

    // We can sort any list of numbers from 1 to the highest number an int can hold
    cout << "How many numbers should we sort? [1 - "<< numeric_limits<int>::max() << "]--> ";
    cin >> n;

    char i;
    cout << "Verbose? [y/n] --> ";
    cin >> i;
    if (tolower(i) == 'y') {
        cout << "Verbose it is!" << endl;
        verbose = true;
    } else {
        verbose = false;
    }

    cout << "Use slow sorters? [y/n] --> ";
    cin >> i;
    if (tolower(i) == 'y') {
        use_slow_sorters = true;
    } else {
        use_slow_sorters = false;
    }

    auto tot_start = high_resolution_clock::now(); // script start time

    vector<int> arr(n);
    for(int i=0; i < n; i++) {
        arr[i] = i+1;
    }

    cout << "Starting!\n\nList length --> " << n << "\n\n";

    if (verbose) {cout << "Created array!  Shuffling... \n ";}


/* -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ [ Quick sort ] -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_*/
    shuffle(arr);
    if (verbose) {
        cout << "\n\n- - - Quicksort starting - - -\n";
    }
    auto quicksort_start = high_resolution_clock::now();
    quicksort(arr, 0, arr.size()-1);
    auto quicksort_stop = high_resolution_clock::now();

    if (verbose) {
        cout << "Quick sort finished. Here is sorted array:" << endl;

        for (auto x : arr) {
            cout << x << " ";
        }
        cout << endl;

        cout << "\n\nShuffling again..." << endl;
    }
    auto quicksort_time = duration_cast<milliseconds>(quicksort_stop - quicksort_start);
    cout << "Quick sort -->     " << quicksort_time.count() << "ms\n";


/* -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ [ Bubble sort ] -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_*/
    if (use_slow_sorters) {
        shuffle(arr);
        if (verbose) {cout << "Shuffled!\n\n- - - Bubblesort starting - - -\n" << endl;}

        auto bubblesort_start = high_resolution_clock::now();
        bubblesort(arr);
        auto bubblesort_stop = high_resolution_clock::now();

        if (verbose) {
            cout << "Bubble sort finished. Here is the sorted array:" << endl;

            for (auto x : arr) {
                cout << x << " ";
            }
            cout << endl;

            cout << "\n\nShuffling again..." << endl;
        }
        auto bubblesort_time = duration_cast<milliseconds>(bubblesort_stop - bubblesort_start);
        cout << "Bubble sort -->    " << bubblesort_time.count() << "ms\n";

    }

/* -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ [ Shell sort ] -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_*/
    shuffle(arr);
    if (verbose) {cout << "Shuffled!\n\n- - - shellsort starting - - -\n" << endl;}

    auto shellsort_start = high_resolution_clock::now();
    shellsort(arr);
    auto shellsort_stop = high_resolution_clock::now();

    if (verbose) {
        cout << "Shell sort finished. Here is the sorted array:" << endl;

        for (auto x : arr) {
            cout << x << " ";
        }
        cout << endl;

        cout << "\n\nShuffling again..." << endl;
    }
    auto shellsort_time = duration_cast<milliseconds>(shellsort_stop - shellsort_start);
    cout << "Shell sort -->     " << shellsort_time.count() << "ms\n";


/* -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ [ Merge sort ] -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_*/
    shuffle(arr);
    if (verbose) {cout << "Shuffled!\n\n- - - mergesort starting - - -\n" << endl;}

    auto mergesort_start = high_resolution_clock::now();
    mergesort(arr, 0, arr.size()-1);
    auto mergesort_stop = high_resolution_clock::now();

    if (verbose) {
        cout << "Merge sort finished. Here is sorted array:" << endl;

        for (auto x : arr) {
            cout << x << " ";
        }
        cout << endl;

        cout << "\n\nShuffling again..." << endl;
    }
    auto mergesort_time = duration_cast<milliseconds>(mergesort_stop - mergesort_start);
    cout << "Merge sort -->     " << mergesort_time.count() << "ms\n";


/* -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ [ Tree sort ] -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_*/
    shuffle(arr);
    if (verbose) {cout << "Shuffled!\n\n- - - treesort starting - - -\n" << endl;}

    auto treesort_start = high_resolution_clock::now();
    treesort(arr);
    auto treesort_stop = high_resolution_clock::now();

    if (verbose) {
        cout << "Tree sort finished. Here is the sorted array:" << endl;

        for (auto x : arr) {
            cout << x << " ";
        }
        cout << endl;

        cout << "\n\nShuffling again..." << endl;
    }
    auto treesort_time = duration_cast<milliseconds>(treesort_stop - treesort_start);
    cout << "Tree sort -->      " << quicksort_time.count() << "ms\n";

/* -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ [ Heap sort ] -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_*/
    shuffle(arr);
    if (verbose) {cout << "Shuffled!\n\n- - - heapsort starting - - -\n" << endl;}

    auto heapsort_start = high_resolution_clock::now();
    heapsort(arr, n);
    auto heapsort_stop = high_resolution_clock::now();

    if (verbose) {
        cout << "Heap sort finished. Here is the sorted array:" << endl;

        for (auto x : arr) {
            cout << x << " ";
        }
        cout << endl;

        cout << "\n\nShuffling again..." << endl;
    }
    auto heapsort_time = duration_cast<milliseconds>(heapsort_stop - heapsort_start);
    cout << "Heap sort -->      " << heapsort_time.count() << "ms\n";


/* -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ [ Pancake sort ] -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_*/
    if (use_slow_sorters) {
        shuffle(arr);
        if (verbose) {cout << "Shuffled!\n\n- - - pancake sort starting - - -\n" << endl;}

        auto pancakesort_start = high_resolution_clock::now();
        pancakesort(arr, n);
        auto pancakesort_stop = high_resolution_clock::now();

        if (verbose) {
            cout << "Pancake sort finished. Here is the sorted array:" << endl;

            for (auto x : arr) {
                cout << x << " ";
            }
            cout << endl;

            cout << "\n\nShuffling again..." << endl;
        }
        auto pancakesort_time = duration_cast<milliseconds>(pancakesort_stop - pancakesort_start);
        cout << "Pancake sort -->   " << pancakesort_time.count() << "ms\n";
    }

/* -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_ [ Gnome sort ] -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_*/
    if (use_slow_sorters) {
        shuffle(arr);
        if (verbose) {cout << "Shuffled!\n\n- - - gnomesort starting - - -\n" << endl;}

        auto gnomesort_start = high_resolution_clock::now();
        gnomesort(arr, n);
        auto gnomesort_stop = high_resolution_clock::now();

        if (verbose) {
            cout << "gnome sort finished. Here is the sorted array:" << endl;

            for (auto x : arr) {
                cout << x << " ";
            }
            cout << endl;

            cout << "\n\nShuffling again..." << endl;
        }
        auto gnomesort_time = duration_cast<milliseconds>(gnomesort_stop - gnomesort_start);
        cout << "Gnome sort -->     " << gnomesort_time.count() << "ms\n";
    }


    auto tot_stop = high_resolution_clock::now();
    auto tot_time = duration_cast<milliseconds>(tot_stop - tot_start);
    if (use_slow_sorters) {
    }

    cout << "\nTotal -->          " << tot_time.count() << "ms\n";

    return 0;
}
/*
You reached the end of the file! Those are just a few sorting
algorithms. Some are good, some aren't. I hope this was useful!
c:
*/
