
#include "GraphWriter.hpp"

#include <iostream>

GraphWriter::GraphWriter()
{
}

void GraphWriter::writeGraph(vector<Vertex>& vertices, vector<Edge>& edges)
{
  writeBasics();
  writeVertices(vertices);
  writeEdges(edges);

  flush();
}

void GraphWriter::writeBasics() 
{
  XMLElement* gexf = _doc.NewElement("gexf");
  XMLElement* meta = _doc.NewElement("meta");
  XMLElement* creator = _doc.NewElement("creator");
  XMLElement* description = _doc.NewElement("description");
  XMLElement* graph = _doc.NewElement("graph");
  XMLElement* nodes = _doc.NewElement("nodes");
  XMLElement* edges = _doc.NewElement("edges");

  XMLText* creatorText = _doc.NewText("CrowGenCpp");
  XMLText* descriptionText = _doc.NewText("generated by CrowGenCpp");

  _doc.InsertEndChild(gexf);
  gexf->InsertEndChild(meta);
  gexf->InsertEndChild(graph);
  meta->InsertEndChild(creator);
  meta->InsertEndChild(description);
  graph->InsertEndChild(nodes);
  graph->InsertEndChild(edges);
  creator->InsertEndChild(creatorText);
  description->InsertEndChild(descriptionText);
}

void GraphWriter::writeVertices(vector<Vertex>& vertices) 
{
  XMLElement* nodes = _doc.FirstChildElement("gexf")->FirstChildElement("graph")
    ->FirstChildElement("nodes");

  for (size_t i = 0; i < vertices.size(); i++)
  {
    Vertex v = vertices.at(i);
    XMLElement* node = _doc.NewElement("node");
    XMLElement* spells = _doc.NewElement("spells");
    XMLElement* spell = _doc.NewElement("spell");

    nodes->InsertEndChild(node);
    node->InsertEndChild(spells);
    spells->InsertEndChild(spell);

    node->SetAttribute("id", v.id());
    node->SetAttribute("label", v.label());

    spell->SetAttribute("start", v.start());
    spell->SetAttribute("end", v.end());
  }
}

void GraphWriter::writeEdges(vector<Edge>& edges) 
{
  XMLElement* edgesxml = _doc.FirstChildElement("gexf")->FirstChildElement("graph")
    ->FirstChildElement("edges");

  for (size_t i = 0; i < edges.size(); i++)
  {
    Edge e = edges.at(i);
    XMLElement* edge = _doc.NewElement("edge");
    XMLElement* spells = _doc.NewElement("spells");
    XMLElement* spell = _doc.NewElement("spell");

    edgesxml->InsertEndChild(edge);
    edge->InsertEndChild(spells);
    spells->InsertEndChild(spell);

    edge->SetAttribute("id", e.id().c_str());
    edge->SetAttribute("source", e.source().id());
    edge->SetAttribute("target", e.target().id());
    edge->SetAttribute("type", e.type().c_str());

    spell->SetAttribute("start", e.start());
    spell->SetAttribute("end", e.end());
  }
}

void GraphWriter::flush()
{
  _doc.SaveFile("out.gexf");
}
