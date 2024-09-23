#__author__ = 'ProBook'
import networkx as nx
#g=nx.Graph()
#g.add_edge('a','b',weight=0.1)
#g.add_edge('b','c',weight=1.5)
#g.add_edge('a','c',weight=1.0)
#g.add_edge('c','d',weight=2.2)
#print(nx.shortest_path(g,'b','d'))
#print(nx.shortest_path(g,'b','d',weight='weight'))

#import matplotlib.pyplot as plt
##import pylab as plt
#f=nx.watts_strogatz_graph(100,8,0.1)
#nx.draw_circular(f,node_color='r')
#plt.savefig('graph_circular.png')
#nx.draw_random(f,node_color='g')
#plt.savefig('graph_random.png')
#nx.draw_spectral(f)
#plt.savefig('graph_spectral.png')
#plt.show()
#
#------------------------

#import matplotlib.pyplot as plt
#import networkx as nx
#G1=nx.watts_strogatz_graph(100,8,0.1)
#
#elarge1 =[(u,v) for (u,v,d) in G1.edges(data=True)]
#elarge2 =[(u,v) for (u,v,d) in G1.edges(data=True)]
#
#pos1=nx.circular_layout(G1)
#pos2=nx.random_layout(G1)
#pos3=nx.spectral_layout(G1)
#
#for k,v in pos2.items():
#    # Shift the x values of every node by 10 to the right
#    v[0] = v[0] +2
#
#for k,v in pos3.items():
#    # Shift the x values of every node by 10 to the right
#    v[0] = v[0] +5
#
#nx.draw_networkx_nodes(G1,pos1,node_size=10,node_color='b')
#nx.draw_networkx_edges(G1,pos1,edgelist=elarge1,width=1,style='solid')
#
#
#nx.draw_networkx_nodes(G1,pos2,node_size=10,node_color='r')
#nx.draw_networkx_edges(G1,pos2,edgelist=elarge2,width=1)
#
#nx.draw_networkx_nodes(G1,pos3,node_size=20,node_color='g')
#nx.draw_networkx_edges(G1,pos3,edgelist=elarge1,width=1,style='solid')
#
#plt.savefig('graphs.png')
#
#plt.show() # display

#------------------------

import matplotlib.pyplot as plt
import networkx as nx

G = nx.star_graph(20)
pos = nx.spring_layout(G)
colors = range(20)
nx.draw(G, pos, node_color='#A0CBE2', edge_color=colors,
        width=4, edge_cmap=plt.cm.Blues, with_labels=False)
plt.show()
