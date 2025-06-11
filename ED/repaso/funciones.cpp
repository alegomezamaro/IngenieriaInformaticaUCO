    //Practica 1: Linear DS
        ⁠push_front (CDArray) 
            if (is_full()){ //Si esta lleno crece
                grow();
            }
            if(!is_empty()){ //Sino esta vacio se desplazan todos los elementos a la siguiente posición
                for(size_t i=size_; i>0; i--){
                    data_[i]=data_[i-1];
                }   
            }
            data_[0]=new_it; //Se almacena el elemento en la primera posición
            size_++; //Se incrementa el tamaño


        ⁠⁠grow (CDArray)
            size_t new_capacity = 2 * capacity_; //Se crea new_capacity con el doble de capacidad
            std::shared_ptr<T[]> new_data(new T[new_capacity], std::default_delete<T[]>()); //Se crea new_data, un puntero compartido de tamaño new_capacity
            for (size_t i = 0; i < size_; i++) { //Mientras i sea menos que el numero de elementos copiamos al nuevo array
                new_data[i] = data_[i % capacity_];
            }
            data_ = new_data; //Se asigna el nuevo array a data_
            capacity_ = new_capacity; //Se asigna la nueva capacidad a capacity_
            front_ = 0; //Se asigna front_ a 0
            back_ = size_ - 1; //Se asigna back_ a la ultima posición (size_-1)


        enque (Queue)
            data_.push_back(new_it); //Se añade new_it al final de la cola


        hook (List)
            n->set_next(pos); //n apunta a pos como siguiente
            n->set_prev(pos->prev()); //n apunta al anterior de pos como anterior 
            pos->prev()->set_next(n); //El anterior de pos apunta a n como siguiente 
            pos->set_prev(n); //pos apunta a n como anterior
            size_++; //Aumentamos el tamaño uno


        unhook (List)
            pos->prev()->set_next(pos->next()); //El anterior de pos apunta al siguiente de pos como siguiente
            pos->next()->set_prev(pos->prev()); //El siguiente de pos apunta al anterior de pos como anterior
            size_--; //Reducimos el tamaño


        ⁠push_front (List)
            insert(begin(), new_it); //Inserta el new_it al principio de la lista


    //Practica 2: KDTree
        ⁠⁠fold (BTree) //[ root left right ]
            if (is_empty()){ //Si el arbol esta vacio lo representamos con []
                out << "[]";
            }
            else { //Si el arbol no esta vacio
                out << "[ " << item() << " "; //Añadimos el [ root
                left().fold(out); //Añadimos el hijo izquierdo
                out << " "; 
                right().fold(out); //Añadimos el hijo derecho
                out << " ]"; //Añadimos ]
            } 


        compute_height (BTree Utils)
            if(t.is_empty()){ //Si el arbol esta vacio retornamos -1
                height = -1;
            }
            else { //Si el arbol no esta vacio devolvemos 1+(altura del hijo mas alto)
                height = 1 + std::max(compute_height(t.left()), compute_height(t.right()));
            }


        compute_size (BTree Utils)
            if(t.is_empty()){ //Si el arbol esta vacio devolvemos 0
                ret_val = 0;
            }
            else { //Si el arbol no esta vacio devolvemos 1+(return left)+(return right) 
                ret_val = 1 + compute_size(t.left()) + compute_size(t.right());
            }


        ⁠⁠prefix_process (BTree Utils) //Root left right
            if(!tree.is_empty()){ //Si el arbol no esta vacio
                retVal = p(tree.item()) && prefix_process(tree.left(), p) && prefix_process(tree.right(), p); //Devolvemos 
            }


        ⁠⁠infix_process (BTree Utils) //Left root right
            if(!tree.is_empty()){ //Si el arbol no esta vacio
                retVal = infix_process(tree.left(), p) && p(tree.item()) && infix_process(tree.right(), p); //Devolvemos
            }


        ⁠⁠postfix_process (BTree Utils) //Left right root
            if(!tree.is_empty()){ //Si el arbol no esta vacio
                retVal = postfix_process(tree.left(), p) && postfix_process(tree.right(), p) && p(tree.item()); //Devolvemos
            }


        fold (KDTree) //dimensiones [ root left right ]
            std::string k_str = std::to_string(k_) + " "; //Almacenamos las dimensiones del kdtre en un string
            out.write(k_str.c_str(), k_str.size()); //Escribimos las dimensiones del espacio
            tree_.fold(out); //Escribimos el arbol binario kdtree


    //Practica 3: AVLTree
        ⁠set_child (AVLNode)
            if(dir == 0){ //Si el hijo es izquierdo
                set_left(new_child); //Añade el hijo izquierdo
            }
            else{ //Si el hijo es derecho
                set_right(new_child); //Añade el hijo derecho
            }


        ⁠⁠balance_factor (AVLTree)
            if (root_ != nullptr) { //Si root existe
                int left_height, right_height; //Definimos las alturas de los hijos
                if(root_->left()){ //Si existe el hijo izquierdo almacenamos su altura
                    left_height=root_->left()->height();
                }
                else{ //Sino la altura sera -1
                    left_height=-1;
                }
                if(root_->right()){ //Si existe el hijo derecho se almacena su altura
                    right_height=root_->right()->height();
                }
                else{ //Sino la altura sera -1
                    right_height=-1;
                }
                bf = left_height - right_height; //Devolvemos la altura izquierda menos la derecha
            }

        
        ⁠⁠insert (AVLTree)
            current_ = AVLTNode<T>::create(k); //Creamos un nuevo nodo con el k y lo almacenamos en current_
            if (parent_ == nullptr) { //Si el nodo padre es nulo, asignar el nodo current_ a root_
                root_ = current_; 
                current_->set_parent(nullptr); //Asignar como padre de current_ nullptr.
            }
            else { //Si el padre no es nulo
                current_->set_parent(parent_); //Asignar como padre a parent_
                if (parent_->item() > k) { //Si el nodo padre es mayor k asignamos el arbol izquierdo
                    parent_->set_left(current_);
                }
                else { //Sino asignamos el arbol derecho
                    parent_->set_right(current_); 
                }
            }
            height_ = std::max(height_, current_level()); //Almacenamos la altura del nodo
            size_++; //Sumamos uno al tamaño


        ⁠⁠find_inorder_sucesor (AVLTree) //Derecha y maximo izquierda
            parent_ = current_; //Asignar current_ a parent_
            current_ = current_->right(); //Asignar el hijo de derecho a current_
            while (current_->left() != nullptr){ //Mientras tenga hijos izquierdos
                parent_ = current_; //Asignar current_ a parent_
                current_ = current_->left(); //Asignar el hijo izquierdo a current_
            }
        

        ⁠⁠rotate (AVLTree) //dir==0 (izquierda) dir==1 (derecha)
            typename AVLTNode<T>::Ref G;
            typename AVLTNode<T>::Ref CN;
            int gpDir;
            G = P->parent(); //Asignamos padre de P (abuelo) a G
            N = P->child(1 - dir); //Obtenemos N (si es izquierda hijo derecho, sino al reves)
            CN = N->child(dir); //Asignamos el hijo derecho de N a CN
            P->set_child(1 - dir, CN); //Asignar a CN como hijo de P
            if (CN != nullptr){ //Si CN no es nulo le asignamos como padre a P
                CN->set_parent(P);
            }
            N->set_child(dir, P); //Asignar a P como hijo de N
            P->set_parent(N); //Asignar a N como padre de P
            if (G != nullptr){ //Si G no es nulo
                if(G->child(0) == P){ //Si el hijo izquierdo de G es P lo almacenamos
                    gpDir = 0;
                }
                else{ //Si es el derecho lo almacenamos
                    gpDir = 1;
                } 
                G->set_child(gpDir, N); //Asignamos N como hijo de G en la posicion de P
            }
            else{ //Si G es nulo
                set_root_node(N); //Asignar N como nodo raiz
            }
            N->set_parent(G); //Asignamos a G como padre de N


        ⁠⁠make_balanced (AVLTree)
            typename AVLTNode<T>::Ref N;
            int bfP, bfN, dir;
            P->update_height(); //Actualizamos la altura del nodo P
            bfP = P->balance_factor(); //Obtenemos el factor de equilibrio de P
            if (std::abs(bfP) > 1){ //Si esta desbalanceado (FE valor absoluto > 1)
                if(bfP < 0){ //Si el fe es menor que cero rotamos a la izquierda, sino derecha
                    dir = 0;
                }
                else{
                    dir = 1;
                }
                N = P->child(dir); //Asignar a N como hijo de P
                bfN = N->balance_factor(); //Obtenemos el factor de equilibrio de N
                if (bfP*bfN < 0){ //Si estan desbalanceados en distinta  dirección
                    rotate(N, dir); //Rotamos N en la direccion de desbalanceo
                }
                P = rotate(P, 1 - dir); //Rotamos P en la direccion contraria al desbalanceo
            }       


    //Practica 4: Priority Queue
        parent (Heap) //(i-1)/2
                return (i - 1) / 2;

        left (Heap) //2i+1
            return (2 * i + 1);

        right (Heap) //2i+2
            return (2 * i + 2);
        
        shift_up (Heap)
            if(i > 0 && comp_((*values_)[i], (*values_)[parent(i)])){ //Mientras el hijo es menor que el padre
                std::swap((*values_)[i], (*values_)[parent(i)]); //Intercambiamos al padre y el hijo
                shift_up(parent(i)); //Repetimos el proceso con el padre
            }


        shift_down (Heap)
            size_t n = i; //Almacenamos el indice de n
            size_t lC = left(i);  //Obtenemos el indice de su hijo izquierdo
            size_t rC = right(i); //Obtenemos el indice de su hijo derecho
            if (lC < last_item_ && comp_((*values_)[lC], (*values_)[n])){ //Si el hijo izquierdo es menor que el padre
                n = lC; //Almacenamos el hijo izquierdo en el padre
            }
            if (rC < last_item_ && comp_((*values_)[rC], (*values_)[n])){ //Si el hijo derecho es menor que el padre
                n = rC; //Almacenamos el hijo derecho en el padre
            }
            if (i != n){ //Si finalmente el padre no es el menor
                std::swap((*values_)[i], (*values_)[n]); //Cambiamos el padre por el hijo menor
                shift_down(n); //Repetimos el proceso con el nuevo padre
            }
        

        is_a_heap (Heap)
            size_t lC = left(root);  //Obtenemos el indice de su hijo izquierdo
            size_t rC = right(root); //Obtenemos el indice de su hijo derecho
            if (lC < last_item_){ //Si el indice del hijo izquierdo es menor que el último elemento del montículo
                if (!comp_((*values_)[root], (*values_)[lC]) || !is_a_heap(lC)){ //Si el root no es menor que el hijo izquierdo y el hijo izquierdo no es un heap
                    ret_val=false; 
                }
            }
            if(rC < last_item_){ //Si el índice del hijo derecho es menor que el último elemento del montículo
                if (!comp_((*values_)[root], (*values_)[rC]) || !is_a_heap(rC)){ //Si el root no es menor que el hijo derecho y el hijo derecho no es un heap
                    ret_val=false;
                }
            }
        

        ⁠⁠heapify (Heap)
            if (size() > 0){ //Si el tamaño del array es mayor que 0
                for (size_t i = (size() / 2) - 1; i < size(); --i){ //Recorremos desde el primer padre con dos hijos
                    shift_down(i); //Llamamos a la función shift_down para equilibrar desde i
                }
            } 


        Heap (Heap)
            last_item_ = values.size(); //Almacenamos el tamaño en last_item_
            heapify(); //Cosntruimos el heap


        is_empty (Heap)
            return last_item_ == 0; //Si last_item_ es 0 true
        
        size (Heap)
            return last_item_; //Devolvemos el tamaño del array
        

        item (Heap)
            return (*values_)[0]; //Devolvemos el primer elemento del array


        insert (Heap)
            if (last_item_ == values_->size()){ //Si esta lleno añadimos un elemento al final
                values_->push_back(new_it);
            }
            else{ //Si no esta lleno añadimos el elemento en la primera posicion libre
                (*values_)[last_item_] = new_it;
            }
            last_item_++; //Aumentamos el tamaño
            shift_up(last_item_ - 1); //Llamamos a la función shift_up para subir el nuevo elemento


        remove (Heap)
            last_item_--; //Disminuimos el tamaño del array
            if (last_item_ > 0){ //Si el tamaño del array es mayor que 0
                std::swap((*values_)[0], (*values_)[last_item_]); //Intercambiamos el primer elemento del array con el último
                shift_down(0); //Llamamos a la función shift_down para bajar el primer elemento
            }
        

        heapsort (Heap)
            Heap<T> heap(values, comp); //Creamos un heap con los valores
            for (size_t i = values.size(); i > 0; i--){ //Recorremos el array desde el final hasta el principio
                heap.remove(); //Eliminamos el primer elemento
            }


        is_empty (Priority Queue)
            return heap_.is_empty(); //Devolvemos si el heap está vacío


        size (Priority Queue)
            return heap_.size(); //Devolvemos el tamaño


        front (Priority Queue)
            return heap_.item(); //Devolvemos el primer elemento


        enqueue (Priority Queue)
            heap_.insert(new_v); //Insertamos el nuevo elemento
        

        dequeue (Priority Queue)
            heap_.remove(); //Eliminamos el primer elemento


    //Practica 5: Dos detector open adressing
        operator<< (IP Utils) //ip.bytes[0] . ip.bytes[1] . ip.bytes[2] . ip.bytes[3]
            out << static_cast<int>(ip.bytes[0]) << "." << static_cast<int>(ip.bytes[1]) << "." << static_cast<int>(ip.bytes[2]) << "."
            << static_cast<int>(ip.bytes[3]); //Salida de la IP en formato decimal
        

        ⁠operator>> (IP Utils)
            std::string input; //Variable para almacenar la cadena de entrada
            in >> input; //Leemos la cadena de entrada
            std::replace(input.begin(), input.end(), '.', ' '); //Reemplazamos los '.' por espacios para poder leer los números
            std::istringstream iss(input); //Creamos un istringstream para poder leer los números separados por espacios
            int a, b, c, d; //Variables para almacenar los números leídos
            if (!(iss >> a >> b >> c >> d) || a < 0 || a > 255 || b < 0 || b > 255 || c < 0 || c > 255 || d < 0 || d > 255) {
                throw std::runtime_error("Ip: wrong input format."); //Comprobamos que los números leídos son válidos
            }
            ip.bytes[0] = static_cast<uint8_t>(a); //Convertimos los números a uint8_t
            ip.bytes[1] = static_cast<uint8_t>(b); 
            ip.bytes[2] = static_cast<uint8_t>(c); 
            ip.bytes[3] = static_cast<uint8_t>(d); 


        ⁠operator++ (Hash Table Iterator)
            do{ 
                ++idx_; //Aumentamos el índice
            }while(idx_ < ht_->size() && !ht_->entry(idx_).is_valid()); //Mientras el índice sea menor que el tamaño de la tabla y la entrada no sea válida


        ⁠operator== (Hash Table Iterator)
            ret_v = table() == other.table() && index() == other.index(); //Comprobamos que la tabla es la misma y que el índice es el mismo


    //Practica 6: WGraph Path
        other (Edge)
            if (n == u_){ //Si n es igual a u devolvemos v
                return v_;
            }
            else{ //Si no lo es devolvemos u
                return u_;
            }


        ⁠add_edge (Graph)
            ret_v = Edge<T, E>::create(u, v, item); //Creamos una arista entre u y v con valor item
            auto u_iter = get_iterator(u); //Almacenamos la lista de aristas de u
            u_iter.it_->second.push_back(ret_v); //Añadimos la arista nueva a la lista
            if(!is_directed()){ //Si el grafo es no dirigido hacemos lo mismo con v
                auto v_iter = get_iterator(v);
                v_iter.it_->second.push_back(ret_v);
            }


        ⁠remove_edge (Graph)
            auto u_iter = get_iterator(u); //Almacenamos la lista de aristas de u
            auto edge_iter = edges_begin(u_iter); //Obtienemos el iterador de la lista de aristas de u
            while(edge_iter != edges_end(u_iter)){ //Recorre la lista de aristas de u
                if((*edge_iter)->other(u) == v){ //Si la arista contrario es v lo borramos
                    edge_iter.it_ = u_iter.it_->second.erase(edge_iter.it_);
                    break;
                }
                else{ //Sino continua con la siguiente arista
                    edge_iter++;
                }
            }
            if(!is_directed()){ //Si el grafo es no dirigido eliminamos tambien en v
                auto v_iter = get_iterator(v);
                edge_iter = edges_begin(v_iter);
                while(edge_iter != edges_end(v_iter)){ 
                    if((*edge_iter)->other(v) == u){ 
                        edge_iter.it_ = v_iter.it_->second.erase(edge_iter.it_); 
                        break;
                    }
                    else{ 
                        edge_iter++; 
                    }
                }
            }


        VertexIterator ⁠find_first (Graph)
            while(iter != vertices_end() && (*iter)->item().key() != value){ //Mientras no encuentre el vertice value avanza 
                iter++;
            } 


        ⁠remove_vertex (Graph)
            auto iter = vertices_.begin(); //Definimos un iterador al principio de la lista de vértices
            while(iter != vertices_.end() && iter->first != v){ //Recorremos los vértices hasta encontrar v
                iter++;
            }
            if(iter != vertices_.end()){ //Si se encontró v
                for(auto& vertex_pair : vertices_){ //Recorre todos los vertices
                    if(vertex_pair.first != v){ //Si es distinto de v
                        auto edge_iter = vertex_pair.second.begin(); //Definimos un iterador al principio de la lista de vértices
                        while(edge_iter != vertex_pair.second.end()){ //Mientras no llegue al final de la lista de vertices
                            if((*edge_iter)->has(v)){ //Si el vertice tiene v en un extremo lo eliminamos
                                edge_iter = vertex_pair.second.erase(edge_iter);
                            }
                            else{ //Si no avanza al siguiente vertice
                                edge_iter++;
                            }
                        }
                    }
                }
                vertices_.erase(iter); //Elimina v
            }   


        EdgeIterator ⁠find_first (Graph)
            while(edge_iter != edges_end(u_iter) && (*edge_iter)->other(*u_iter)->item().key() != value){ //Mientras no encuentre el vertice value avanza 
                edge_iter++;
            }


        ⁠get_edges (Graph)
            for(auto v_iter = g.vertices_begin(); v_iter != g.vertices_end(); ++v_iter){ //Recorre los vértices del grafo
                for(auto e_iter = g.edges_begin(v_iter); e_iter != g.edges_end(v_iter); ++e_iter){ //Recorre las aristas de todos los vertices
                    if (g.is_directed() || (*e_iter)->first() == *v_iter){ //Si es dirigido o el vertice actual es el extremo izquierdo (no repetir u-v y v-u)
                      es.push_back(*e_iter); //Añade la arista al vector    
                    }
                }
            }
