#pragma once
#include "list.h"
#include <string>
#include <fstream>
using namespace std;

class vertex {
public:
	char name = ' ';
	int height = 0;
	int edgeFlow = 0;
};

class edge {
public:
	char uName = ' ';
	int uNumb = 0;
	char vName = ' ';
	int vNumb = 0;
	int flow = 0;
	int capacity = -1;
};

class graph {
private:
	list<edge> edges;
	list<vertex> vertexes;
public:
	graph() {

	}

	void inputVertex(fstream& in)
	{
		in >> noskipws;
		if (!in.is_open()) throw "Файл не открыт!";
		while (!in.eof()) {
			char c = ' ';
			vertex curVertex;
			in >> c;
			bool newVertex = true;
			for (int i = 0; i < vertexes.getSize(); i++) {
				if (vertexes.at(i)->name == c) {
					newVertex = false;
					break;
				}
			}
			if (newVertex) {
				curVertex.name = c;
				vertexes.push_back(curVertex);
			}
			in >> c;
			if (c != ' ')
				throw "Ошибка во входных данных!";
			in >> c;
			newVertex = true;
			for (int i = 0; i < vertexes.getSize(); i++)
				if (vertexes.at(i)->name == c) {
					newVertex = false;
					break;
				}
			if (newVertex) {
				curVertex.name = c;
				vertexes.push_back(curVertex);
			}
			while (c != '\n' && !in.eof()) in >> c;
		}
		in.close();
	}

	void inputEdge(fstream& in)
	{
		if (vertexes.getSize() == 0) throw "Вершины не заданы";
		in >> noskipws;
		if (!in.is_open()) throw "Файл не открыт!";
		char c;
		while (!in.eof()) {
			edge curEdge;
			in.get(curEdge.uName);
			in >> c;
			if (c != ' ') throw "Ошибка во входных данных!";
			in >> curEdge.vName;
			in >> c;
			if (c != ' ') throw "Ошибка во входных данных!";
			in >> curEdge.capacity;
			if (curEdge.capacity == -1) throw "Ошибка во входных данных!";
			for (int i = 0; i < vertexes.getSize(); i++) {
				if (vertexes.at(i)->name == curEdge.uName) curEdge.uNumb = i;
				if (vertexes.at(i)->name == curEdge.vName) curEdge.vNumb = i;
			}
			edges.push_back(curEdge);
			in << c;
		}
		cout << endl;
		for (int i = 0; i < edges.getSize(); i++) {
			cout << edges.at(i)->capacity << " ";
			cout << edges.at(i)->flow << " ";
			cout << edges.at(i)->uName << "-";
			cout << edges.at(i)->uNumb << " ";
			cout << edges.at(i)->vName << "-";
			cout << edges.at(i)->vNumb << endl;
		}
	}

	bool push(int uNumb)
	{
		for (int i = 0; i < edges.getSize(); i++) {
			if (edges.at(i)->uNumb == uNumb) {
				if (edges.at(i)->flow == edges.at(i)->capacity) continue;
				if (vertexes.at(uNumb)->height > vertexes.at(edges.at(i)->vNumb)->height) {
					int flow = min(edges.at(i)->capacity - edges.at(i)->flow,
						vertexes.at(uNumb)->edgeFlow);
					vertexes.at(uNumb)->edgeFlow -= flow;
					vertexes.at(edges.at(i)->vNumb)->edgeFlow += flow;
					edges.at(i)->flow += flow;
					updateReverseEdgeFlow(i, flow);
					return true;
				}
			}
		}
		return false;
	}

	void relabel(int uNumb)
	{
		int maxHeight = INT_MAX;
		for (int i = 0; i < edges.getSize(); i++) {
			if (edges.at(i)->uNumb == uNumb) {
				if (edges.at(i)->flow == edges.at(i)->capacity) continue;
				if (vertexes.at(edges.at(i)->vNumb)->height < maxHeight) {
					maxHeight = vertexes.at(edges.at(i)->vNumb)->height;
					vertexes.at(uNumb)->height = maxHeight + 1;
				}
			}
		}
	}

	void preflow(int indexStart)
	{

		vertexes.at(indexStart)->height = vertexes.getSize();
		for (int i = 0; i < edges.getSize(); i++) {
			if (edges.at(i)->uNumb == indexStart) {
				edges.at(i)->flow = edges.at(i)->capacity;
				vertexes.at(edges.at(i)->vNumb)->edgeFlow += edges.at(i)->flow;
				edge newEdge;
				newEdge.flow = -edges.at(i)->flow;
				newEdge.capacity = 0;
				newEdge.uNumb = edges.at(i)->vNumb;
				newEdge.uName = vertexes.at(edges.at(i)->vNumb)->name;
				newEdge.vNumb = indexStart;
				newEdge.vName = vertexes.at(indexStart)->name;
				edges.push_back(newEdge);
			}
		}
	}

	void updateReverseEdgeFlow(int indexArr, int flow)
	{
		int uNumb = edges.at(indexArr)->vNumb;
		int vNumb = edges.at(indexArr)->uNumb;
		for (int j = 0; j < edges.getSize(); j++) {
			if (edges.at(j)->vNumb == vNumb && edges.at(j)->uNumb == uNumb) {
				edges.at(j)->flow -= flow;
				return;
			}
		}
		edge newEdge;
		newEdge.flow = 0;
		newEdge.capacity = flow;
		newEdge.uNumb = uNumb;
		newEdge.uName = vertexes.at(uNumb)->name;
		newEdge.vNumb = vNumb;
		newEdge.vName = vertexes.at(vNumb)->name;
		edges.push_back(newEdge);
	}

	int overFlowVertex(list<vertex>& temp)
	{
		for (int i = 1; i < temp.getSize() - 1; i++)
			if (temp.at(i)->edgeFlow > 0)
				return i;
		return -1;
	}

	int MaxFlow() {
		if (vertexes.getSize() == 0) throw "Вершины не заданы";
		if (edges.getSize() == 0) throw "Рёбра не заданы";
		int indexStart = 0;
		preflow(indexStart);
		while (overFlowVertex(vertexes) != -1) {
			int overFlowIndex = overFlowVertex(vertexes);
			if (!push(overFlowIndex))
				relabel(overFlowIndex);
		}
		return vertexes.back().edgeFlow;
	}


};