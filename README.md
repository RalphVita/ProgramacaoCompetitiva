# Programação Competitiva
Exercícios de programação competitivas tirados de vjudge.net

```shell
docker run --name myvjudge -it -v  C:/Users/wvita/Source/Repos/RalphVita/ProgramacaoCompetitiva:/home/pc ubuntu:vjudge bash
```
ou
```shell
docker container exec -it myvjudge /bin/bash
```

### Estruturas

#### Grafo
Armazena informação de conectividade entre vértices

~~~ c++
    int AdjMat[V][V]
~~~
__Ou__

~~~ c++
    vector<vector<pair<int, int>>>
~~~

#### Union-Find/Disjoint Sets
* Encontrar o conjunto que um elemento pertence
  ~~~ c++
    UF.findSet(i)
  ~~~
* Testar se dois elementos pertencem ao mesmo conjunto
  ~~~ c++
    UF.isSameSet(a, b)
  ~~~
* Fazer a união de dois conjuntos
  ~~~ c++
    //Coloca os elementos do conjunto em que a está, no conjunto em que b está.
    UF.unionSet(a, b);
  ~~~

#### Segment Tree
* Encontrar o índice do menor elemento no intervalo [i…j]
  ~~~ c++
    RMQ(i, j) 
  ~~~
* Para retornar o máximo é só multiplicar a entrada por -1.
  ~~~ c++
    st.update(k, k, -x);
    -RMQ(i, j)
  ~~~

#### Fenwick Tree
* Quantas vezes os inteiros entre a e b aparecem em um array?
  ~~~ c++
    RSQ(a, b) 
  ~~~