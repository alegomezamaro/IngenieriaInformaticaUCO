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
            size--; //Reducimos el tamaño


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
                retVal = p(tree.item()); //Devolvemos root
                retVal = retVal && prefix_process(tree.left(), p); //Devolvemos anterior + el hijo izquierdo (y sus hijos)
                retVal = retVal && prefix_process(tree.right(), p); //Devolvemos anterior + el hijo derecho (y sus hijos)
            }


        ⁠⁠infix_process (BTree Utils) //Left root right
            if(!tree.is_empty()){ //Si el arbol no esta vacio
                retVal = infix_process(tree.left(), p); //Devolvemos anterior + el hijo izquierdo (y sus hijos)
                retVal = retVal && p(tree.item()); //Devolvemos root
                retVal = retVal && infix_process(tree.right(), p); //Devolvemos anterior + el hijo derecho (y sus hijos)
            }


        ⁠⁠postfix_process (BTree Utils) //Left right root
            if(!tree.is_empty()){ //Si el arbol no esta vacio
                retVal = postfix_process(tree.left(), p); //Devolvemos anterior + el hijo izquierdo (y sus hijos)
                retVal = retVal && postfix_process(tree.right(), p); //Devolvemos root
                retVal = retVal && p(tree.item()); //Devolvemos anterior + el hijo derecho (y sus hijos)
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

        ///////////////////////////////////////
        ⁠⁠insert (AVLTree)
            current_ = AVLTNode<T>::create(k); //Crear un nuevo nodo con el valor k.
            if (parent_ == nullptr) { //Si el nodo padre es nulo, asignar el nodo actual a la raíz.
                root_ = current_; //Asignar el nodo raíz al nodo actual.
                current_->set_parent(nullptr); //Asignar el nodo padre a nullptr.
            }
            else { //Sino
                current_->set_parent(parent_); //Asignar el nodo padre al nodo actual.
                if (parent_->item() > k) { //Si el valor del nodo padre es mayor que el valor k, asignar el subárbol izquierdo al nodo padre.
                    parent_->set_left(current_); //Asignar el subárbol izquierdo al nodo padre.
                }
                else { //Sino
                    parent_->set_right(current_); //Asignar el subárbol derecho al nodo padre.
                }
            }
            height_ = std::max(height_, current_level());
            size_++;


        ⁠⁠find_inorder_sucesor (AVLTree)
            parent_ = current_; //Asignar el nodo padre al nodo actual.
            current_ = current_->right(); //Asignar el subárbol derecho al nodo actual.
            while (current_->left() != nullptr){ //Mientras el subárbol izquierdo no sea nulo.
                parent_ = current_; //Asignar el nodo padre al nodo actual.
                current_ = current_->left(); //Asignar el subárbol izquierdo al nodo actual.
            }
        
        ⁠⁠rotate (AVLTree)
            typename AVLTNode<T>::Ref G;
            typename AVLTNode<T>::Ref CN;
            int gpDir;
            G = P->parent(); //Nodo padre del nodo P.
            N = P->child(1 - dir); //Nodo hijo del nodo P.
            CN = N->child(dir); //Nodo hijo del nodo N.
            P->set_child(1 - dir, CN); //Asignar el hijo del nodo P al nodo hijo del nodo N.
            if (CN != nullptr){ //Si el hijo del nodo N no es nulo
                CN->set_parent(P); //Asignar el nodo padre al nodo P.
            }
            N->set_child(dir, P); //Asignar el hijo del nodo N al nodo P.
            P->set_parent(N); //Asignar el nodo padre al nodo N.
            if (G != nullptr){ //Si el nodo padre no es nulo
                gpDir = (G->child(0) == P) ? 0 : 1; //Asignar el hijo del nodo padre al nodo P.
                G->set_child(gpDir, N); //Asignar el hijo del nodo padre al nodo N.
            }
            else{ //Sino
                set_root_node(N); //Asignar el nodo raíz al nodo N.
            }
            N->set_parent(G); //Asignar el nodo padre al nodo N.

        ⁠⁠make_balanced (AVLTree)
            typename AVLTNode<T>::Ref N; //Hijo del nodo padre.
            int bfP, bfN, dir; //Factor de equilibrio del nodo padre, hijo y dirección.
            P->update_height(); //Actualizar la altura del nodo padre.
            // First, update subtree root node height because we have just done
            // an insertion/deletion in the subtree.
            bfP = P->balance_factor(); //Factor de equilibrio del nodo padre.
            if (std::abs(bfP) > 1){ //Si el factor de equilibrio del nodo padre es mayor que 1, el árbol está desbalanceado.
                dir = (bfP < 0) ? 0 : 1; //Asignar la dirección del nodo padre.
                N = P->child(dir); //Asignar el hijo del nodo padre.
                bfN = N->balance_factor(); //Factor de equilibrio del hijo del nodo padre.
                if (bfP*bfN >= 0){ //Si el producto de los factores de equilibrio es mayor o igual a 0, el árbol está desbalanceado.
                    P = rotate(P, 1 - dir); //Asignar el nodo padre al hijo del nodo padre.
                }
                else{ //Sino
                    rotate(N, dir); //Asignar el hijo del nodo padre al nodo padre.
                    P = rotate(P, 1 - dir); //Asignar el nodo padre al hijo del nodo padre.
                }
            }
            // Second, compute balance factor.
            // Third, check the balance factor to do rotations if needed.
            // Remember: update subtree_root if any rotation is done.        
            

    //Practica 4: Priority Queue
        //⁠Entera, entrará alguna priority_queue o heap

        parent (Heap)
                return (i - 1) / 2; //Devolvemos el padre

        left (Heap)
            return (2 * i + 1); //Devolvemos el hijo izquierdo

        right (Heap)
            return (2 * i + 2); //Devolvemos el hijo derecho
        
        shift_up (Heap)
            if(i > 0 && comp_((*values_)[i], (*values_)[parent(i)])){ //Mientras el padre es mayor que el hijo
                std::swap((*values_)[i], (*values_)[parent(i)]); //Cambiamos el padre por el hijo
                shift_up(parent(i)); //Llamamos recursivamente a la función para seguir subiendo el hijo
            }

        shift_down (Heap)
            size_t n = i; //Indice del padre
            size_t lC = left(i);  //Indice del hijo izquierdo
            size_t rC = right(i); //Indice del hijo derecho
            if (lC < last_item_ && comp_((*values_)[lC], (*values_)[n])){ //Si el hijo izquierdo es menor que el padre
                n = lC; //Actualizamos el índice del padre
            }
            if (rC < last_item_ && comp_((*values_)[rC], (*values_)[n])){ //Si el hijo derecho es menor que el padre
                n = rC; //Actualizamos el índice del padre
            }
            if (i != n){ //Si el padre no es el menor
                std::swap((*values_)[i], (*values_)[n]); //Cambiamos el padre por el hijo
                shift_down(n); //Llamamos recursivamente a la función para seguir bajando el padre
            }
        
        is_a_heap (Heap)
            size_t lC = left(root);  //Indice del hijo izquierdo
            size_t rC = right(root); //Indice del hijo derecho
            if (lC < last_item_){ //Si el indice del hijo izquierdo es menor que el último elemento del montículo
                if (!comp_((*values_)[root], (*values_)[lC]) || !is_a_heap(lC)){ // Si el elemento actual no es menor que el hijo izquierdo y el hijo izquierdo no es un heap
                    ret_val=false; 
                }
            }
            else if(rC < last_item_){ //Si el índice del hijo derecho es menor que el último elemento del montículo
                if (!comp_((*values_)[root], (*values_)[rC]) || !is_a_heap(rC)){ //Si el elemento actual no es menor que el hijo derecho y el hijo derecho no es un heap
                    ret_val=false;
                }
            }
        
        ⁠⁠heapify (Heap)
            if (size() > 0){ //Si el tamaño del array es mayor que 0
                for (size_t i = (size() / 2) - 1; i < size(); --i){ //Recorremos el array desde la mitad hasta el principio
                    shift_down(i); //Llamamos a la función shift_down para bajar el padre
                }
            } 

        Heap (Heap)
            last_item_ = values.size(); //Guardamos el tamaño del array
            heapify(); //Construimos el heap

        is_empty (Heap)
            return last_item_ == 0; //Si el último elemento es 0, el heap está vacío
        
        size (Heap)
            return last_item_; //Devolvemos el tamaño del array
        
        item (Heap)
            return (*values_)[0]; //Devolvemos el primer elemento del array

        insert (Heap)
            if (last_item_ == values_->size()){ //Si el tamaño del array es igual al tamaño del heap
                values_->push_back(new_it); //Añadimos el nuevo elemento al final del array
            }
            else{ //Sino
                (*values_)[last_item_] = new_it; //Añadimos el nuevo elemento al final del heap
            }
            last_item_++; //Aumentamos el tamaño del array
            shift_up(last_item_ - 1); //Llamamos a la función shift_up para subir el nuevo elemento

        remove (Heap)
            last_item_--; //Disminuimos el tamaño del array
            if (last_item_ > 0){ //Si el tamaño del array es mayor que 0
                std::swap((*values_)[0], (*values_)[last_item_]); //Intercambiamos el primer elemento del array con el último
                shift_down(0); //Llamamos a la función shift_down para bajar el primer elemento
            }
        
        heapsort (Heap)
            Heap<T> heap(values, comp); //Creamos un heap con el array
            for (size_t i = values.size(); i > 0; i--){ //Recorremos el array desde el final hasta el principio

                heap.remove(); //Llamamos a la función remove para eliminar el primer elemento del heap
            }

        is_empty (Priority Queue)
            return heap_.is_empty(); //Devolvemos si el heap está vacío

        size (Priority Queue)
            return heap_.size(); //Devolvemos el tamaño del heap

        front (Priority Queue)
            return heap_.item(); //Devolvemos el primer elemento del heap

        enqueue (Priority Queue)
            heap_.insert(new_v); //Insertamos el nuevo elemento en el heap
        
        dequeue (Priority Queue)
            heap_.remove(); //Eliminamos el primer elemento del heap


    //Practica 5: Dos detector open adressing
        operator<< (IP Utils)
            out << static_cast<int>(ip.bytes[0]) << "." << static_cast<int>(ip.bytes[1]) << "." << static_cast<int>(ip.bytes[2]) << "."
            << static_cast<int>(ip.bytes[3]); //Salida de la dirección IP en formato decimal
        
        ⁠operator>> (IP Utils)
            std::string input; //Variable para almacenar la cadena de entrada
            in >> input; //Leemos la cadena de entrada
            std::replace(input.begin(), input.end(), '.', ' '); //Reemplazamos los '.' por espacios para poder leer los números
            std::istringstream iss(input); //Creamos un istringstream para poder leer los números separados por espacios
            int a, b, c, d; //Variables para almacenar los números leídos
            if (!(iss >> a >> b >> c >> d) || a < 0 || a > 255 || b < 0 || b > 255 || c < 0 || c > 255 || d < 0 || d > 255) { //Comprobamos que los números leídos son válidos sino muestra un error
                throw std::runtime_error("Ip: wrong input format."); //Lanzamos una excepción si el formato es incorrecto
            }
            //Convertimos los números a uint8_t
            ip.bytes[0] = static_cast<uint8_t>(a); //Convertimos el número a uint8_t
            ip.bytes[1] = static_cast<uint8_t>(b); //Convertimos el número a uint8_t
            ip.bytes[2] = static_cast<uint8_t>(c); //Convertimos el número a uint8_t
            ip.bytes[3] = static_cast<uint8_t>(d); //Convertimos el número a uint8_t

        ⁠operator++ (Hash Table Iterator)
            do{ 
                ++idx_; // Aumentamos el índice
            }while (idx_ < ht_->size() && !ht_->entry(idx_).is_valid()); //Mientras el índice sea menor que el tamaño de la tabla y la entrada no sea válida, aumentamos el índice

        ⁠operator== (Hash Table Iterator)
            ret_v = table() == other.table() && index() == other.index(); //Comprobamos que la tabla es la misma y que el índice es el mismo


    //Practica 6: WGraph Path
        other (Edge)
            if (n == u_){ //Si n es igual a u
                return v_;
            }
            else{ //Sino
                return u_;
            }

        ⁠add_edge (Graph)
            ret_v = Edge<T, E>::create(u, v, item); // Crea un nuevo borde entre u y v con el ítem dado
            auto u_iter = get_iterator(u); // Obtiene el iterador al vértice u
            u_iter.it_->second.push_back(ret_v); // Añade el borde a la lista de bordes incidentes en u
            if(!is_directed()){ // Si el grafo es no dirigido, también debemos añadir el borde a la lista de bordes incidentes en v
                auto v_iter = get_iterator(v); // Obtiene el iterador al vértice v
                v_iter.it_->second.push_back(ret_v); // Añade el borde a la lista de bordes incidentes en v
            }

        ⁠remove_edge (Graph)
            auto u_iter = get_iterator(u); // Obtiene el iterador al vértice u
            auto edge_iter = edges_begin(u_iter); // Obtiene el iterador al principio de la lista de bordes incidentes en u
            while(edge_iter != edges_end(u_iter)){ // Recorre los bordes incidentes en u desde el principio hasta el final
                if((*edge_iter)->other(u) == v){ // Si el borde actual tiene v como otro extremo
                    edge_iter.it_ = u_iter.it_->second.erase(edge_iter.it_); // Elimina el borde de la lista de bordes incidentes en u
                    break;
                }
                else{
                    edge_iter++; // Avanza al siguiente borde
                }
            }
            if(!is_directed()){ // Si el grafo es no dirigido, también debemos eliminar el borde de la lista de bordes incidentes en v
                auto v_iter = get_iterator(v); // Obtiene el iterador al vértice v
                edge_iter = edges_begin(v_iter); // Obtiene el iterador al principio de la lista de bordes incidentes en v
                while(edge_iter != edges_end(v_iter)){ // Recorre los bordes incidentes en v desde el principio hasta el final
                    if((*edge_iter)->other(v) == u){ // Si el borde actual tiene u como otro extremo
                        edge_iter.it_ = v_iter.it_->second.erase(edge_iter.it_); // Elimina el borde de la lista de bordes incidentes en v
                        break;
                    }
                    else{ // Sino, avanza al siguiente borde 
                        edge_iter++; 
                    }
                }
            }

        ⁠remove_vertex (Graph)
            auto iter = vertices_.begin(); // Obtiene el iterador al principio de la lista de vértices
            while(iter != vertices_.end() && iter->first != v){ // Recorre los vértices desde el principio hasta el final
                iter++;
            }
            if(iter != vertices_.end()){ // Si se encontró el vértice v en la lista de vértices
                for(auto& vertex_pair : vertices_){ // Recorre todos los pares de vértices y sus listas de bordes
                    if(vertex_pair.first != v){ // Si el vértice actual no es v
                        auto edge_iter = vertex_pair.second.begin(); // Obtiene el iterador al principio de la lista de bordes incidentes en el vértice actual
                        while(edge_iter != vertex_pair.second.end()){ // Recorre los bordes incidentes en el vértice actual desde el principio hasta el final
                            if((*edge_iter)->has(v)){ // Si el borde actual tiene v como uno de sus extremos
                                edge_iter = vertex_pair.second.erase(edge_iter); // Elimina el borde de la lista de bordes incidentes en el vértice actual                    
                            }
                            else{ // Sino, avanza al siguiente borde
                                edge_iter++;
                            }
                        }
                    }
                }
                vertices_.erase(iter); // Elimina el vértice v de la lista de vértices
            }

        VertexIterator ⁠find_first (Graph)
            while(iter != vertices_end() && (*iter)->item().key() != value){ //Recorre los vértices desde el principio hasta el final
                iter++; //Avanza al siguiente vértice
            }    

        EdgeIterator ⁠find_first (Graph)
            while(edge_iter != edges_end(u_iter) && (*edge_iter)->other(*u_iter)->item().key() != value){ //Recorre los bordes desde el principio hasta el final
                edge_iter++; //Avanza al siguiente borde
            }

        ⁠get_edges (Graph)
            for(auto v_iter = g.vertices_begin(); v_iter != g.vertices_end(); ++v_iter){ //Recorre los vértices desde el principio hasta el final
                for(auto e_iter = g.edges_begin(v_iter); e_iter != g.edges_end(v_iter); ++e_iter){ //Recorre los bordes desde el principio hasta el final
                    if (g.is_directed() || (*e_iter)->first() == *v_iter){ //Si el grafo es dirigido o el borde comienza en el vértice actual
                      es.push_back(*e_iter); //Añade el borde al vector de bordes       
                    }
                }
            }
