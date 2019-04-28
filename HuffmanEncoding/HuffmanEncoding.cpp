#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>

using namespace std;

struct Node
{// A Tree node
	char ch;
	int freq;
	Node *left, *right;
};

struct comp
{// Comparison object to be used to order the heap
	bool operator()(Node* l, Node* r)
	{
		// highest priority item has lowest frequency
		return l->freq > r->freq;
	}
};

Node* getNode(char ch, int freq, Node* left, Node* right)
{ // Function to allocate a new tree node
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

void encode(Node* root, string str, unordered_map<char, string> &huffmanCode)
{// traverse the Huffman Tree and store Huffman Codes in a map.
	if (root == nullptr)
		return;

	// found a leaf node
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

void decode(Node* root, int &index, string str)
{// traverse the Huffman Tree and decode the encoded string
	if (root == nullptr) {
		return;
	}

	// found a leaf node
	if (!root->left && !root->right)
	{
		cout << root->ch;
		return;
	}

	index++;

	if (str[index] == '0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}

string buildHuffmanTree(string text)
{// Builds Huffman Tree and decode given input text


	// count frequency of appearance of each character and store it in a map
	unordered_map<char, int> freq;
	for (char ch : text) {
		freq[ch]++;
	}

	// Create a priority queue to store live nodes of
	// Huffman tree;
	priority_queue<Node*, vector<Node*>, comp> pq;

	// Create a leaf node for each character and add it
	// to the priority queue.
	for (auto pair : freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	// do till there is more than one node in the queue
	while (pq.size() != 1)
	{
		// Remove the two nodes of highest priority
		// (lowest frequency) from the queue
		Node *left = pq.top(); pq.pop();
		Node *right = pq.top();	pq.pop();

		// Create a new internal node with these two nodes
		// as children and with frequency equal to the sum
		// of the two nodes' frequencies. Add the new node
		// to the priority queue.
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	// root stores pointer to root of Huffman Tree
	Node* root = pq.top();

	// traverse the Huffman Tree and store Huffman Codes
	// in a map. Also prints them
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	cout << "Huffman Codes are :\n" << '\n';
	for (auto pair : huffmanCode) {
		cout << pair.first << " " << pair.second << '\n';
	}

	cout << "\nOriginal string was :\n" << text << '\n';

	// print encoded string
	string str = "";
	for (char ch : text) {
		str += huffmanCode[ch];
	}

	cout << "\nEncoded string is :\n" << str << '\n';

	// traverse the Huffman Tree again and this time
	// decode the encoded string
	int index = -1;
	cout << "\nDecoded string is: \n";
	while (index < (int)str.size() - 2) {
		decode(root, index, str);
	}

	return str;
}

void compress(int dataSetSize)
{
	ifstream inFile;
	string size = to_string(dataSetSize) + ".txt";
	inFile.open("D:\\Documents\\Habib University Spring 2019\\Data Structures II\\Project\\HuffmanEncoding\\HuffmanEncoding\\Dataset\\" + size);
	
	if (!inFile)
	{
		cout << "Could not open file " << endl;
		exit(1);
	}
	
	string text((std::istreambuf_iterator<char>(inFile)),
		(std::istreambuf_iterator<char>()));

	string code = buildHuffmanTree(text);

	cout << "\n\n\nThe returned encoded string is " << code.size() << " bits wide."<< endl;
	float compressionRatio = (code.size()/(dataSetSize * 8.0f));
	cout << "Compression is " << (compressionRatio < 1 ? "recommended." : "not recommended.") << endl;
	cout << "Compression Ratio is " << compressionRatio << endl;
}

int main()
{	
	int setSizes[] = { 500, 1000, 10000, 100000 };
	char cont;
	for (int size : setSizes)
	{
		cout << "Data Compression of set size" << size << "." << endl;
		compress(size);
		cout << "Compression Complete" << endl;
		if (size != 100000)
		{
			cout << "Enter any character to move to next data set" << endl;
			cin >> cont;
			system("CLS");
		}
	}

	return 0;
}


