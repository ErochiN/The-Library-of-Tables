/**
 * https://github.com/ErochiN/The-Library-of-Tables 
 * @file Table.h
 * @author Ерохин Степан (KwizyOne@outlook.com)
 * @date 2023
 * @brief Шаблонные классы для работы с табличными данными
 *
 * Реализация таблицы на основе связанных списков с возможностью:
 * - Динамического добавления/удаления столбцов и строк
 * - Гибкого управления данными
 * - Форматированного вывода в консоль
 *
 * Основные классы:
 * - Cells<T> - столбец таблицы (односвязный список элементов)
 * - Table<T> - управление коллекцией столбцов
 *
 * Пример использования:
 * @code
 * Table<int> table;
 * table.AddCells("ID");
 * table.AddCells("Name");
 * table.AddInCells_PushBack(0, 1);
 * table.AddInCells_PushBack(1, "John");
 * table.PrintTable();
 * @endcode
 *
 * @version 1.0
 * @license MIT
 */

#pragma once
#include <iostream>
#include <iomanip>
#include <string>

template <typename T>
class Cells
{
public:
	Cells<T>* pNext;

	Cells(Cells<T>* pNext = nullptr);
	Cells(std::string name, Cells<T>* pNext = nullptr);
	~Cells();

	void SetName(std::string name);

	int GetSize() const;
	std::string GetName() const;

	void PushBack(T data);
	void PushHead(T data);
	void PushIndex(const int index, T data);

	void DeleteBack();
	void DeleteHead();
	void DeleteIndex(const int index);
	void Clear();

	T& operator[](const int index);

private:
	template <typename T1>
	class Node
	{
	public:
		T1 data;
		Node<T1>* pNext;

		Node(T1 data = T(), Node<T1>* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}
	};


	Node<T>* head;
	std::string name;
	unsigned int size;
};

template <typename T>
class Table
{
public:
	Table();
	~Table();

	void AddCells(std::string name);
	void AddInCells_PushBack(const int index, T data);
	void AddInCells_PushIndex(const int indexCells, const int indexInCells, T data);

	void DeleteAdd_Back(const int index);
	void DeleteAdd_Index(const int indexCells, const int indexElement);

	void PrintTable();
	void SetXSize(int xSize);

	std::string GetNameCells(const int index);
	T& GetData(const int indexT, const int indexC);

private:
	std::string name;
	int size;
	Cells<T>* headCells;

	int xSize;

	void PrintLine(int columns);
};

template<typename T>
Cells<T>::Cells(Cells<T>* pNext)
{
	this->head = nullptr;
	this->size = 0;
	this->name = "Standart Name";
	this->pNext = pNext;
}

template<typename T>
Cells<T>::Cells(std::string name, Cells<T>* pNext)
{
	this->head = nullptr;
	this->size = 0;
	this->name = name;
	this->pNext = pNext;
}

template<typename T>
Cells<T>::~Cells()
{
	this->Clear();
}

template<typename T>
void Cells<T>::SetName(std::string name)
{
	this->name = name;
}

template<typename T>
int Cells<T>::GetSize() const
{
	return this->size;
}

template<typename T>
std::string Cells<T>::GetName() const
{
	return this->name;
}

template<typename T>
void Cells<T>::PushBack(T data)
{
	if (this->head == nullptr)
		this->head = new Node<T>(data);
	else
	{
		Node<T>* cur = this->head;

		while (cur->pNext != nullptr)
			cur = cur->pNext;

		cur->pNext = new Node<T>(data);
	}
	this->size++;
}

template<typename T>
void Cells<T>::PushHead(T data)
{
	if (this->head == nullptr)
		this->head = new Node<T>(data);
	else
		this->head = new Node<T>(data, this->head);
	this->size++;
}

template<typename T>
void Cells<T>::PushIndex(const int index, T data)
{
	if (index < 0 || index > size)
		throw std::out_of_range("Index out of range");

	if (index == 0)
		this->PushHead(data);
	else
	{
		Node<T>* cur = this->head;

		for (int i = 0; i < index - 1; i++)
			cur = cur->pNext;

		if (cur == nullptr)
			throw std::runtime_error("Invalid position");

		Node<T>* NewNode = new Node<T>(data);
		NewNode->pNext = cur->pNext;
		cur->pNext = NewNode;
		this->size++;
	}
}

template<typename T>
void Cells<T>::DeleteBack()
{
	if (head == nullptr) return;

	if (head->pNext == nullptr)
	{
		delete head;
		head = nullptr;
	}
	else
	{
		Node<T>* cur = this->head;

		while (cur->pNext != nullptr)
			cur = cur->pNext;

		delete cur->pNext;
		cur->pNext = nullptr;
	}
	this->size--;
}

template<typename T>
void Cells<T>::DeleteHead()
{
	if (this->head == nullptr)
		return;

	Node<T>* temp = this->head->pNext;
	delete this->head;
	this->head = temp;
	this->size--;
}

template<typename T>
void Cells<T>::DeleteIndex(const int index)
{
	if (index == 0)
		this->DeleteHead();
	else
	{

		Node<T>* cur = this->head;

		for (int i = 0; i < index - 1; i++)
			cur = cur->pNext;

		Node<T>* temp = cur->pNext;
		cur->pNext = temp->pNext;

		delete temp;

		this->size--;
	}

}

template<typename T>
void Cells<T>::Clear()
{
	while (this->head != nullptr)
	{
		Node<T>* temp = this->head;
		this->head = this->head->pNext;
		delete temp;
	}
	this->size = 0;
}

template<typename T>
T& Cells<T>::operator[](const int index)
{
	if (index < 0 || index >= size)
		throw std::out_of_range("Index out of range");

	Node<T>* cur = this->head;

	for (int i = 0; i < index; i++)
		cur = cur->pNext;

	return cur->data;
}

template<typename T>
Table<T>::Table()
{
	this->headCells = nullptr;
	this->size = 0;
	this->name = "Table Name";
}

template<typename T>
Table<T>::~Table()
{
	while (headCells != nullptr)
	{
		Cells<T>* temp = headCells;
		headCells = headCells->pNext;
		delete temp;
	}
}

template<typename T>
void Table<T>::AddCells(std::string name)
{
	try
	{
		if (headCells == nullptr)
		{
			headCells = new Cells<T>(name);
		}
		else
		{
			Cells<T>* cur = headCells;
			while (cur->pNext != nullptr)
				cur = cur->pNext;
			cur->pNext = new Cells<T>(name);
		}
		size++;
	}
	catch (...)
	{
		throw std::runtime_error("Failed to add column");
	}
}

template<typename T>
void Table<T>::AddInCells_PushBack(const int index, T data)
{
	if (index < 0 || index >= size)
		throw std::out_of_range("Column index out of range");

	Cells<T>* cur = this->headCells;

	for (int i = 0; i < index && cur != nullptr; i++)
		cur = cur->pNext;

	if (cur == nullptr)
		throw std::runtime_error("Column not found");

	cur->PushBack(data);
}

template<typename T>
void Table<T>::AddInCells_PushIndex(const int indexCells, const int indexInCells, T data)
{
	Cells<T>* cur = headCells;

	for (int i = 0; i < indexCells && cur != nullptr; i++)
		cur = cur->pNext;

	if (cur != nullptr)
		cur->PushIndex(indexInCells, data);
}

template<typename T>
void Table<T>::DeleteAdd_Back(const int index)
{
	Cells<T>* cur = this->headCells;

	for (int i = 0; i < index; i++)
		cur = cur->pNext;

	cur->DeleteBack();
}

template<typename T>
void Table<T>::DeleteAdd_Index(const int indexCells, const int indexElement)
{
	if (indexCells < 0 || indexCells >= size)
		throw std::out_of_range("Column index out of range");

	Cells<T>* cur = headCells;

	for (int i = 0; i < indexCells && cur != nullptr; i++)
		cur = cur->pNext;

	if (cur == nullptr)
		throw std::runtime_error("Column not found");

	if (indexElement < 0 || indexElement >= cur->GetSize())
		throw std::out_of_range("Element index out of range");

	cur->DeleteIndex(indexElement);
}

template<typename T>
void Table<T>::PrintTable()
{
	if (this->size == 0) {
		std::cout << "❌ Таблица пуста!\n";
		return;
	}

	int totalColumns = this->size + 1; 
	int totalWidth = totalColumns * xSize + (totalColumns + 1);
	int titlePadding = (totalWidth - this->name.length() - 2) / 2;
	std::cout << "|" << std::setw(titlePadding) << "" << this->name
		<< std::setw(totalWidth - this->name.length() - titlePadding - 2) << "" << "|\n";

	PrintLine(totalColumns);

	std::cout << "|" << std::setw(xSize) << std::left << " " << "|";
	for (int i = 0; i < this->size; i++)
	{
		std::string columnNumber = "Col " + std::to_string(i + 0);
		std::cout << std::setw(xSize) << std::left << columnNumber << "|";
	}
	std::cout << "\n";

	PrintLine(totalColumns);

	std::cout << "|" << std::setw(xSize) << std::left << " " << "|";
	for (int i = 0; i < this->size; i++)
	{
		std::string name = this->GetNameCells(i);
		std::cout << std::setw(xSize) << std::left << name << "|";
	}
	std::cout << "\n";

	PrintLine(totalColumns);

	int maxRows = 0;
	Cells<T>* cur = this->headCells;
	while (cur)
	{
		if (cur->GetSize() > maxRows)
			maxRows = cur->GetSize();
		cur = cur->pNext;
	}

	for (int row = 0; row < maxRows; row++)
	{
		std::cout << "|" << std::setw(xSize) << std::left << ("Row " + std::to_string(row + 0));

		cur = this->headCells;
		while (cur)
		{
			std::string value = (row < cur->GetSize()) ? std::to_string(cur->operator[](row)) : " ";
			std::cout << "|" << std::setw(xSize) << std::left << value;
			cur = cur->pNext;
		}

		std::cout << "|\n";
		PrintLine(totalColumns);
	}
}

template<typename T>
void Table<T>::SetXSize(int xSize)
{
	this->xSize = xSize;
}

template<typename T>
std::string Table<T>::GetNameCells(const int index)
{
	if (index < 0 || index >= size)
		throw std::out_of_range("Column index out of range");

	Cells<T>* cur = this->headCells;

	for (int i = 0; i < index; i++)
		cur = cur->pNext;

	return cur->GetName();
}

template<typename T>
T& Table<T>::GetData(const int indexT, const int indexC)
{
	if (indexT < 0 || indexT >= size)
		throw std::out_of_range("Column index out of range");

	Cells<T>* cur = this->headCells;
	for (int i = 0; i < indexT && cur != nullptr; i++)
		cur = cur->pNext;

	if (cur == nullptr)
		throw std::runtime_error("Column not found");

	return cur->operator[](indexC);
}

template<typename T>
void Table<T>::PrintLine(int columns)
{
	std::cout << "|";
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < xSize; j++)
			std::cout << "-";
		std::cout << "|";
	}
	std::cout << std::endl;
}