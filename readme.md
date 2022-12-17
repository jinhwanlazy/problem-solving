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
| [algconvexhull](.misc/snippets/cpp_2d_geometry.snippets#L512) | convex hull algorithm | [boj_1708](boj_1708) [boj_3679](boj_3679) [boj_3878](boj_3878) [boj_4225](boj_4225) [boj_7420](boj_7420) [boj_9240](boj_9240) [boj_10254](boj_10254) [boj_19586](boj_19586) |
| [algrotatingcalipers](.misc/snippets/cpp_2d_geometry.snippets#L541) | rotating calipers | [boj_9240](boj_9240) [boj_10254](boj_10254) |
| [algshoelace](.misc/snippets/cpp_2d_geometry.snippets#L573) | the shoelace algorithm, that calculates area of the 2d polygon | [boj_2166](boj_2166) |

## GRAPH
| Keyword | Description | Used in |
| ------- | ----------- | ------- |
| [algdijkstra](.misc/snippets/cpp_graph.snippets#L14) | Dijkstra's shortest path algorithm | [boj_1753](boj_1753) [boj_16958](boj_16958) |
| [algbellman](.misc/snippets/cpp_graph.snippets#L89) | Bellman-Ford, shortest path algorithm. | [boj_1865](boj_1865) [boj_11657](boj_11657) |
| [algunionfind](.misc/snippets/cpp_graph.snippets#L228) | Union Find Set data structure | [boj_1043](boj_1043) [boj_1197](boj_1197) [boj_1647](boj_1647) [boj_1774](boj_1774) [boj_2109](boj_2109) [boj_2162](boj_2162) [boj_3108](boj_3108) [boj_4195](boj_4195) [boj_4386](boj_4386) [boj_9372](boj_9372) [boj_10216](boj_10216) [boj_16724](boj_16724) [boj_17472](boj_17472) [boj_20040](boj_20040) |
| [algtoposort](.misc/snippets/cpp_graph.snippets#L352) | Topological sort algorithm | [boj_1766](boj_1766) [boj_2252](boj_2252) [boj_2623](boj_2623) |
| [algtarjanscc](.misc/snippets/cpp_graph.snippets#L487) | Tarjan's strongly connected components algorithm | [boj_2150](boj_2150) [boj_3648](boj_3648) [boj_3977](boj_3977) [boj_4013](boj_4013) [boj_4196](boj_4196) [boj_9466](boj_9466) [boj_11280](boj_11280) [boj_11281](boj_11281) [boj_16367](boj_16367) |
| [algbipartite](.misc/snippets/cpp_graph.snippets#L566) | Bipartite matching algorithm | [boj_1014](boj_1014) [boj_1017](boj_1017) [boj_1671](boj_1671) [boj_1867](boj_1867) [boj_2188](boj_2188) [boj_2191](boj_2191) [boj_4376](boj_4376) [boj_11014](boj_11014) [boj_11375](boj_11375) [boj_11376](boj_11376) [boj_11377](boj_11377) [boj_11378](boj_11378) [boj_14750](boj_14750) |
| [algedmondskarp](.misc/snippets/cpp_graph.snippets#L625) | Edmonds-Karp, max flow algorithm. |  |
| [algdinic](.misc/snippets/cpp_graph.snippets#L808) | Dinic's max flow algorithm. | [boj_1420](boj_1420) [boj_2365](boj_2365) [boj_6086](boj_6086) [boj_11495](boj_11495) [boj_13161](boj_13161) |

## NUMBER THEORY
| Keyword | Description | Used in |
| ------- | ----------- | ------- |
| [algsieve](.misc/snippets/cpp_number_theory.snippets#L1) | Sieve of Eratosthenes, finds all prime numbers in given range | [boj_17104](boj_17104) [boj_17134](boj_17134) |
| [algmodpow](.misc/snippets/cpp_number_theory.snippets#L24) | modulus pow | [boj_5615](boj_5615) |
| [algxgcd](.misc/snippets/cpp_number_theory.snippets#L45) | Extended euclidean algorithm | [boj_3955](boj_3955) [boj_9267](boj_9267) [boj_14565](boj_14565) [boj_20412](boj_20412) |

## STRING
| Keyword | Description | Used in |
| ------- | ----------- | ------- |
| [algkmp](.misc/snippets/cpp_string.snippets#L1) | KMP, string search algorithm | [boj_1305](boj_1305) [boj_1786](boj_1786) [boj_4354](boj_4354) [boj_5525](boj_5525) |
| [algpalindrome](.misc/snippets/cpp_string.snippets#L54) | Manaker's longest palindromic substring algorithm | [boj_13275](boj_13275) [boj_16163](boj_16163) |
| [algzalgorithm](.misc/snippets/cpp_string.snippets#L103) | z algorithm | [boj_13713](boj_13713) |

## OTHERS
| Keyword | Description | Used in |
| ------- | ----------- | ------- |
| [alglis](.misc/snippets/cpp_others.snippets#L73) | LIS, longest incereasing subsequence algorithm | [boj_2352](boj_2352) [boj_2568](boj_2568) [boj_14002](boj_14002) |
| [algfft](.misc/snippets/cpp_others.snippets#L118) | FFT, Fast Fourier Transform algorithm | [boj_1067](boj_1067) [boj_10531](boj_10531) [boj_16287](boj_16287) [boj_17104](boj_17104) [boj_17134](boj_17134) [boj_20176](boj_20176) |
| [algbigint](.misc/snippets/cpp_others.snippets#L155) | Big integer class | [boj_15576](boj_15576) [boj_15740](boj_15740) |

## TREE
| Keyword | Description | Used in |
| ------- | ----------- | ------- |
| [clssegtree](.misc/snippets/cpp_tree.snippets#L1) | Segment tree class | [boj_2042](boj_2042) [boj_2357](boj_2357) [boj_11505](boj_11505) [boj_14268](boj_14268) [boj_14287](boj_14287) [boj_14288](boj_14288) [boj_16975](boj_16975) [boj_16978](boj_16978) |
| [clsfenwicktree](.misc/snippets/cpp_tree.snippets#L199) | Fenwick tree, binary indexed tree | [boj_2042](boj_2042) |


# Solutions with description
| Name | Tags |
| ---- | ---- |
| [BOJ1074 - Z](boj_1074) | morton code, Z-order |
| [BOJ5977 - Mowing the Lawn](boj_5977) | deque, deque dp, dp, ds |
| [BOJ11401 - 이항 계수 3](boj_11401) | combinatorics, exponentiation by squaring, fermat's little thm, math, modular multiplicative inverse, number theory |
| [BOJ15678 - 연세워터파크](boj_15678) | deque, deque dp, dp, ds, priority queue, segtree |
| [BOJ18614 - Cosmic Crossroads](boj_18614) | 3d, d&c, geom, math |
| [Foobar - Power Hungry](foobar_power-hungry) | dp |

