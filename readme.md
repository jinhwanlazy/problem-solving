Personal workbench for competitive programming. 
It is mainly consisted of 3 parts.

1. ***Snippets***: Predefined algorithms&data structures, which can be loaded through tab-completion in vim editor.
2. ***Solutions***: Solutions of problems.
3. ***Scripts***: Utilities to build&test solutions

# Snippets
Snippets are defined in [UltiSnips](https://github.com/SirVer/ultisnips) format.
They are located under [`.misc/snippets/`](.misc/snippets/)

## 2D GEOMETRY
| Keyword | Description | Used in |
| ------- | ----------- | ------- |
| [algconvexhull](.misc/snippets/cpp_2d_geometry.snippets#L494) | convex hull algorithm | [boj_1708](boj_1708) [boj_3679](boj_3679) [boj_3878](boj_3878) [boj_7420](boj_7420) [boj_10254](boj_10254) [boj_19586](boj_19586) |
| [algrotatingcalipers](.misc/snippets/cpp_2d_geometry.snippets#L523) | rotating calipers | [boj_10254](boj_10254) |
| [algshoelace](.misc/snippets/cpp_2d_geometry.snippets#L555) | the shoelace algorithm, that calculates area of the 2d polygon | [boj_2166](boj_2166) |

## GRAPH
| Keyword | Description | Used in |
| ------- | ----------- | ------- |
| [algdijkstra](.misc/snippets/cpp_graph.snippets#L14) | Dijkstra's shortest path algorithm | [boj_1753](boj_1753) |
| [algbellman](.misc/snippets/cpp_graph.snippets#L89) | Bellman-Ford, shortest path algorithm. | [boj_1865](boj_1865) [boj_11657](boj_11657) |
| [algunionfind](.misc/snippets/cpp_graph.snippets#L228) | Union Find Set data structure | [boj_1043](boj_1043) [boj_1197](boj_1197) [boj_1647](boj_1647) [boj_1717](boj_1717) [boj_1774](boj_1774) [boj_1976](boj_1976) [boj_2162](boj_2162) [boj_2887](boj_2887) [boj_4195](boj_4195) [boj_4386](boj_4386) [boj_9372](boj_9372) [boj_10216](boj_10216) [boj_17472](boj_17472) [boj_20040](boj_20040) |
| [algtoposort](.misc/snippets/cpp_graph.snippets#L316) | Topological sort algorithm | [boj_1766](boj_1766) [boj_2252](boj_2252) |
| [algtarjanscc](.misc/snippets/cpp_graph.snippets#L451) | Tarjan's strongly connected components algorithm | [boj_2150](boj_2150) [boj_3648](boj_3648) [boj_3977](boj_3977) [boj_4013](boj_4013) [boj_4196](boj_4196) [boj_11280](boj_11280) [boj_11281](boj_11281) [boj_16367](boj_16367) |
| [algbipartite](.misc/snippets/cpp_graph.snippets#L530) | Bipartite matching algorithm | [boj_1014](boj_1014) [boj_1017](boj_1017) [boj_1671](boj_1671) [boj_1867](boj_1867) [boj_2188](boj_2188) [boj_11014](boj_11014) [boj_11375](boj_11375) [boj_11376](boj_11376) [boj_11377](boj_11377) [boj_11378](boj_11378) [boj_14750](boj_14750) |
| [algedmondskarp](.misc/snippets/cpp_graph.snippets#L588) | Edmonds-Karp, max flow algorithm. |  |
| [algdinic](.misc/snippets/cpp_graph.snippets#L771) | Dinic's max flow algorithm. | [boj_1420](boj_1420) [boj_2365](boj_2365) [boj_6086](boj_6086) [boj_13161](boj_13161) |

## STRING
| Keyword | Description | Used in |
| ------- | ----------- | ------- |
| [algkmp](.misc/snippets/cpp_string.snippets#L1) | KMP, string search algorithm | [boj_1305](boj_1305) [boj_1786](boj_1786) [boj_4354](boj_4354) [boj_5525](boj_5525) |


# Solutions with description
| Name | Tags |
| ---- | ---- |
| [BOJ1074 - Z](boj_1074) | morton code, Z-order |
| [BOJ5977 - Mowing the Lawn](boj_5977) | deque, deque dp, dp, ds |
| [BOJ15678 - ??????????????????](boj_15678) | deque, deque dp, dp, ds, priority queue, segtree |
| [Foobar - Doomsday Fuel](foobar_doomsday-fuel) | math, markov chain |
| [Foobar - Find the Access Codes](foobar_find-the-access-codes) | dp |
| [Foobar - Power Hungry](foobar_power-hungry) | dp |

