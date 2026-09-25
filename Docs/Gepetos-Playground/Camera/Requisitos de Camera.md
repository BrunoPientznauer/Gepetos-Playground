Os requisitos de camera do player para  o projeto são os seguintes
- A visão deverá ser em estilo top-down 'isométrico', estilo jogos como  Death Door e Yokai  Watch.
- A câmera deve seguir o player com um pequeno delay e usando funções como easing para manter a fluidez do movimento, sem a rigidez de um clipping na posição do player.
- O player deve estar sempre visível, portanto sempre que algum objeto estiver no caminho entre a camera e o player, deverá ser ignorado ou suavizado pelo rendering de ao adicionar transparência nos pixeis que estão a frente do player.
- O usuário não será capaz de mover livremente a rotação da câmera