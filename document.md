

Check UML Folder for UML tree: (screenshot:)[Search Engine UML.pdf](https://github.com/tgicherusmu/assignment-4-search-engine-michael-d-and-trevor-g-main/files/11391556/Search.Engine.UML.pdf)

Filehandler:
The FileHandler class is part of a search engine project and contains several methods to manage and query the search index built from documents. The data structures used here include sets and unordered sets, which allow for efficient storage and retrieval of unique items. 

QHUI(QueryHandler-UserInterface):
This code is part of a search engine project. The main data structure used in this project is an AVL tree, which is implemented through the FileHandler class. An interactive interface for the user to load data files, execute search queries, and display search results. The primary data structure used is an AVL tree implemented in the FileHandler class, which offers efficient search, insert, and delete operations.

Tree:
This block of code defines an AVL tree, a self-balancing binary search tree. The purpose of using an AVL tree in this project is to store data in a way that ensures efficient search, insertion, and deletion operations.

IndexHandler:
This block of code is part of a search engine project. It is designed to index documents, persons, and organizations for later retrieval based on certain keywords.

FilterEntry:
designed to store a name (such as a person’s name or an organization name) and a collection of unique identifiers (UUIDs) associated with the name. The data structure chosen for storing the UUIDs is an unordered set, which allows for efficient storage and retrieval of unique items.

IndexEntry:
This block of code is part of a search engine project and defines a class called IndexEntry. The IndexEntry class is designed to store a word and a collection of document names (or UUIDs) associated with that word, along with the frequency of the word in each document.

Document:
This function parses components in the string file and adds them to the index. It also adds persons and organizations to the index. Document is used to query the index for documents based on certain criteria.

QueryEngine:
This function takes in words from documents and cleans words. Words are trimmed and stemmed using porter2_stemmer function.

Porter2_Stemmer:
This class will go get the root of each word, so we do not end up repeating the same word when it is used in different ways. 
