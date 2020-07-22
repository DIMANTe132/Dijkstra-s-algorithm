/*!
\file
\brief Файл реализующий третью лабораторную работу.

Задача:
Написать программу, реализующую алгоритм дейкстры на произвольном графе, представленном в виде матрицы смежности или списка смежности.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include "list"

using namespace std;

/**
\brief Структура элемента графа
\param vertex − номер вершины
\param weight − вес вершины

\code
struct Element
{
	int vertex;
	int weight;

	Element(int vertex, int weight)
	{
		this->vertex = vertex;
		this->weight = weight;
	}
};
	\endcode
\authors Tereshin D.D
 */
struct Element
{
	int vertex;
	int weight;

	Element(int vertex, int weight)
	{
		this->vertex = vertex;
		this->weight = weight;
	}
};

/**
\brief Структура минимального пути
\param cost − стоимость пути
\param path − ветор вершин кратчайшего пути

\code
struct MinPath
{
	int cost;
	vector<int> path;
};
	\endcode
\authors Tereshin D.D
 */
struct MinPath
{
	int cost;
	vector<int> path;
};

/**
\brief Функция сплитит строку на вектор строк по какому-то делителю
\param str − строка
\param delimeter − делитель
\return vector<string> - вектор полученных строк

\code
vector<string> Split(string str, const string delimeter)
{
	int i = 0;
	vector<string> splitStr;
	while (true)
	{
		int pos = str.find(delimeter);
		if (pos == string::npos)
			break;

		string s = str.substr(0, pos);
		str.erase(0, pos + delimeter.length());
		splitStr.push_back(s);
	}
	if (str != "")
		splitStr.push_back(str);
	return splitStr;
}
	\endcode
\authors Tereshin D.D
 */
vector<string> Split(string str, const string delimiter)
{
	int i = 0;
	vector<string> splitStr;
	while (true)
	{
		int pos = str.find(delimiter);
		if (pos == string::npos)
			break;
		
		string s = str.substr(0, pos);
		str.erase(0, pos + delimiter.length());
		splitStr.push_back(s);
	}
	splitStr.push_back(str);
	return splitStr;
}

/**
\brief Функция реализующая алгоритм Дейкстры
\param data − данные путей vector<Element>*\link<Element>*
\param count − количество вершин
\param start − стартовая вершина
\param end − конечная вершина

\code
template <typename T>
string Dijkstra(const T* data, int count, int start, int end)
{
	vector<MinPath> result(count);
	vector<int> skip;

	int minVertex = start - 1, helperVertex = 0;
	int minValue = numeric_limits<int>::max();

	int counter = 0;
	for (auto i = data[minVertex].begin(); i != data[minVertex].end(); i++)
	{
		if (minVertex == counter)
			result[counter].cost = i->weight;
		else
			result[counter].cost = numeric_limits<int>::max();

		result[counter].path.push_back(start);
		counter++;
	}

	for (int j = 0; j < count; j++)
	{
		counter = 0;
		for (auto i = data[minVertex].begin(); i != data[minVertex].end(); i++)
		{
			bool fix = false;
			for (int num : skip)
				if (num == counter)
				{
					fix = true;
					break;
				}

			if (fix == false)
			{
				if (i->weight != 0)
				{
					if (result[counter].cost > result[minVertex].cost + i->weight)
					{
						result[counter].cost = result[minVertex].cost + i->weight;
						result[counter].path = result[minVertex].path;
						result[counter].path.push_back(counter + 1);
					}
					if (minValue > i->weight)
					{
						minValue = i->weight;
						helperVertex = counter;
					}
				}
			}
			counter++;
		}
		skip.push_back(minVertex);
		if (minValue == numeric_limits<int>::max())
		{
			for (int i = 0; i < count; i++)
			{
				bool fix = false;
				for (int num : skip)
					if (num == i)
					{
						fix = true;
						break;
					}

				if (fix == false && minValue > result[i].cost)
				{
					minValue = result[i].cost;
					helperVertex = i;
				}
			}
		}
		minValue = numeric_limits<int>::max();
		minVertex = helperVertex;
	}

	cout << "Shortest way: " << result[end - 1].cost << endl;
	for (int x = 0; x < result[end - 1].path.size(); x++)
	{
		if (result[end - 1].path.size() - 1 == x)
			cout << result[end - 1].path[x];
		else
			cout << result[end - 1].path[x] << "->";
	}
	cout << endl;
	return "Ok";
}
	\endcode
\authors Tereshin D.D
 */
template <typename T>
string Dijkstra(const T* data, int count, int start, int end)
{
	vector<MinPath> result(count);
	vector<int> skip;

	int minVertex = start - 1, helperVertex = 0;
	int minValue = numeric_limits<int>::max();

	int counter = 0;
	for (auto i = data[minVertex].begin(); i != data[minVertex].end(); i++)
	{
		if (minVertex == counter)
			result[counter].cost = i->weight;
		else
			result[counter].cost = numeric_limits<int>::max();

		result[counter].path.push_back(start);
		counter++;
	}

	for (int j = 0; j < count; j++)
	{
		counter = 0;
		for (auto i = data[minVertex].begin(); i != data[minVertex].end(); i++)
		{
			bool fix = false;
			for (int num : skip)
				if (num == counter)
				{
					fix = true;
					break;
				}

			if (fix == false)
			{
				if (i->weight != 0)
				{
					if (result[counter].cost > result[minVertex].cost + i->weight)
					{
						result[counter].cost = result[minVertex].cost + i->weight;
						result[counter].path = result[minVertex].path;
						result[counter].path.push_back(counter + 1);
					}
					if (minValue > i->weight)
					{
						minValue = i->weight;
						helperVertex = counter;
					}
				}
			}
			counter++;
		}
		skip.push_back(minVertex);
		if (minValue == numeric_limits<int>::max())
		{
			for (int i = 0; i < count; i++)
			{
				bool fix = false;
				for (int num : skip)
					if (num == i)
					{
						fix = true;
						break;
					}

				if (fix == false && minValue > result[i].cost)
				{
					minValue = result[i].cost;
					helperVertex = i;
				}
			}
		}
		minValue = numeric_limits<int>::max();
		minVertex = helperVertex;
	}

	cout << "Shortest way: " << result[end - 1].cost << endl;
	for (int x = 0; x < result[end - 1].path.size(); x++)
	{
		if (result[end - 1].path.size() - 1 == x)
			cout << result[end - 1].path[x];
		else
			cout << result[end - 1].path[x] << "->";
	}
	cout << endl;
	return "Ok";
}

/**
\brief Функция преобразующая и разбивающая строку для дальнейшей работы программы
\param split − строка для преобразования
\return vector<Element*>

Код функции выглядит следующим образом:
\code
vector<Element*> Fragmentation(vector<string> split)
{
	vector<Element*> elements;
	for (int i = 0; i < split.size(); i++)
	{
		if (split[i] != "")
		{
			split[i].erase(0, 1);
			split[i].erase(split[i].length() - 1, split[i].length());
			vector<string> VerAndWeight = Split(split[i], ",");
			stringstream streamZero(VerAndWeight[0]);
			stringstream streamOne(VerAndWeight[1]);
			int vertex, weight;
			streamZero >> vertex;
			streamOne >> weight;
			Element* el = new Element(vertex, weight);
			elements.push_back(el);
		}
	}
	return elements;
}
	\endcode
\authors Tereshin D.D
 */
vector<Element*> Fragmentation(vector<string> split)
{
	vector<Element*> elements;
	for (int i = 0; i < split.size(); i++)
	{
		if (split[i] != "")
		{
			split[i].erase(0, 1);
			split[i].erase(split[i].length() - 1, split[i].length());
			vector<string> VerAndWeight = Split(split[i], ",");
			stringstream streamZero(VerAndWeight[0]);
			stringstream streamOne(VerAndWeight[1]);
			int vertex, weight;
			streamZero >> vertex;
			streamOne >> weight;
			Element* el = new Element(vertex, weight);
			elements.push_back(el);
		}
	}
	return elements;
}

/**
\brief Функция создающая структуру данных отоносительно параметра type
\param count − количество вершин
\param type − тип хранения данных
\param vertexes − массив вершин
\param start − стартовая вершина
\param end − конечная вершина
\return void

Код функции выглядит следующим образом:
\code
	string Conversion(int count, string type, string* vertexes, int start, int end)
	{
		if (type == "matrix")
		{
			vector<Element>* matrix = new vector<Element>[count];
			for (int i = 0; i < count; i++)
			{
				vector<string> split = Split(vertexes[i], ":");
				stringstream streamVer(split[0]);
				int ver;
				streamVer >> ver;
				string v = split[1];
				split = Split(v, "->");
				vector<Element*> elements = Fragmentation(split);

				bool flag = false;
				for (int j = 1; j <= count; j++)
				{
					for (Element* el : elements)
					{
						if (el->vertex == j)
						{
							matrix[i].push_back(*el);
							flag = true;
						}
					}
					if (!flag)
					{
						Element* newEl = new Element(j, 0);
						matrix[i].push_back(*newEl);
					}
					flag = false;
				}
			}
			for (int i = 0; i < count; i++)
			{
				for (int j = 0; j < count; j++)
				{
					cout << matrix[i][j].weight << "\t";
				}
				cout << endl;
			}
			return Dijkstra(matrix, count, start, end);
		}

		else if(type == "link")
		{
			list<Element>* link = new list<Element>[count];
			for (int i = 0; i < count; i++)
			{
				vector<string> split = Split(vertexes[i], ":");
				stringstream streamVer(split[0]);
				int ver;
				streamVer >> ver;
				string v = split[1];
				split = Split(v, "->");
				vector<Element*> elements = Fragmentation(split);

				bool flag = false;
				for (int j = 1; j <= count; j++)
				{
					for (Element* el : elements)
					{
						if (el->vertex == j)
						{
							link[i].push_back(*el);
							flag = true;
						}
					}
					if (!flag)
					{
						Element* newEl = new Element(j, 0);
						link[i].push_back(*newEl);
					}
					flag = false;
				}
			}
			for (int i = 0; i < count; i++)
			{
				cout << i + 1 << ":";
				for (auto it = link[i].begin(); it != link[i].end(); it++)
				{
					cout << " (" << it->vertex << "," << it->weight << ")";
				}
				cout << endl;
			}
			return Dijkstra (link, count, start, end);
		}
		else
			return "Error type";
	}
	\endcode
\authors Tereshin D.D
 */
string Conversion(int count, string type, string* vertexes, int start, int end)
{
	if (type == "matrix")
	{
		vector<Element>* matrix = new vector<Element>[count];
		for (int i = 0; i < count; i++)
		{
			vector<string> split = Split(vertexes[i], ":");
			stringstream streamVer(split[0]);
			int ver;
			streamVer >> ver;
			string v = split[1];
			split = Split(v, "->");
			vector<Element*> elements = Fragmentation(split);

			bool flag = false;
			for (int j = 1; j <= count; j++)
			{
				for (Element* el : elements)
				{
					if (el->vertex == j)
					{
						matrix[i].push_back(*el);
						flag = true;
					}
				}
				if (!flag)
				{
					Element* newEl = new Element(j, 0);
					matrix[i].push_back(*newEl);
				}
				flag = false;
			}
		}
		for (int i = 0; i < count; i++)
		{
			for (int j = 0; j < count; j++)
			{
				cout << matrix[i][j].weight << "\t";
			}
			cout << endl;
		}
		return Dijkstra(matrix, count, start, end);
	}

	else if(type == "link")
	{
		list<Element>* link = new list<Element>[count];
		for (int i = 0; i < count; i++)
		{
			vector<string> split = Split(vertexes[i], ":");
			stringstream streamVer(split[0]);
			int ver;
			streamVer >> ver;
			string v = split[1];
			split = Split(v, "->");
			vector<Element*> elements = Fragmentation(split);

			bool flag = false;
			for (int j = 1; j <= count; j++)
			{
				for (Element* el : elements)
				{
					if (el->vertex == j)
					{
						link[i].push_back(*el);
						flag = true;
					}
				}
				if (!flag)
				{
					Element* newEl = new Element(j, 0);
					link[i].push_back(*newEl);
				}
				flag = false;
			}
		}
		for (int i = 0; i < count; i++)
		{
			cout << i + 1 << ":";
			for (auto it = link[i].begin(); it != link[i].end(); it++)
			{
				cout << " (" << it->vertex << "," << it->weight << ")";
			}
			cout << endl;
		}
		return Dijkstra (link, count, start, end);
	}
	else
		return "Error type";
}

/**
\brief Функция парсящая входные строки
\param argc − количество передающихся параметров
\param argv[] − входные строки
\return void

Код функции выглядит следующим образом:
\code
	
	\endcode
\authors Tereshin D.D
 */
string Parsing(int argc, char* argv[])
{
	if (argc > 1)
	{
		string linkOfFile = argv[1];
		ifstream file(linkOfFile);
		if (file)
		{
			string str;
			string type;
			int countOfVertex;
			getline(file, str);
			try
			{
				countOfVertex = atoi(str.c_str());
			}
			catch (const std::exception&)
			{
				return "Error in file";
			}
			getline(file, str);
			type = str;

			string* graph = new string[countOfVertex];
			int StartVertex = 0;
			int EndVertex = 0;
			int j = 0;
			while (getline(file, str))
			{
				graph[j] = str;
				j++;
			}

			for (int i = 2; i < argc; i++)
			{
				string numberOfVertex = argv[i];

				if (numberOfVertex.find("--start_vertex") != string::npos)
				{
					if (i + 1 < argc)
						StartVertex = atoi(argv[i + 1]);
				}

				if (numberOfVertex.find("--end_vertex") != string::npos)
				{
					if (i + 1 < argc)
						EndVertex = atoi(argv[i + 1]);
				}
			}
			if (StartVertex == 0 || EndVertex == 0)
				return "Error start or end vertex";

			return Conversion(countOfVertex, type, graph, StartVertex, EndVertex);
		}
		return "File error";
	}
	return "Argc error";
}

/**
\brief Основная функция программы
\param argc − количество передающихся параметров
\param argv[] − входные строки
\return int

\code
	int main(int argc, char* argv[])
	{
		cout << "result: " << Parsing(argc, argv) << endl;

		return 0;
	}
	\endcode
\authors Tereshin D.D
 */
int main(int argc, char* argv[])
{
	cout << "result: " << Parsing(argc, argv) << endl;

	return 0;
}