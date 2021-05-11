# SoftbodySimulationSystem OGL3
Softbody Simulation System -- a framework and for softbody objects simulation and comparison of algorithm implementations with sample code instances.
Using OpenGL 3

## References

* [Miao Song](https://dblp.uni-trier.de/pers/hd/s/Song_0001:Miao), Serguei A. Mokhov, and Peter Grogono. 2009. Designing an interactive OpenGL slide-based presentation of the softbody simulation system for teaching and learning of computer graphics techniques. In Proceedings of the 2nd Canadian Conference on Computer Science and Software Engineering (C3S2E '09), Bipin C. Desai and Carson K. Leung (Eds.). ACM, New York, NY, USA, 131-136. DOI=[10.1145/1557626.1557647](http://dx.doi.org/10.1145/1557626.1557647)
* Miao Song and Peter Grogono. 2009. Application of advanced rendering and animation techniques for 3D games to softbody modeling and animation. In Proceedings of the 2nd Canadian Conference on Computer Science and Software Engineering (C3S2E '09), Bipin C. Desai and Carson K. Leung (Eds.). ACM, New York, NY, USA, 89-100. DOI=[10.1145/1557626.1557640](http://dx.doi.org/10.1145/1557626.1557640)
* Song, Miao. "Dynamic deformation of uniform elastic two-layer objects.", Master's thesis, arXiv preprint [arXiv:0907.4364](https://arxiv.org/abs/0907.4364) (2009).


# Important updates and notes
1. Removed Simulation.h and Simulation.cpp from source code, but added a single main.cpp
2. main.cpp can render a demo scene for softbody simulation, including a viewspace, and 3 softbody entities. 
3. Added resources/shaders/core.fs and resources/shaders/core.vs
4. Added shader.h to compile and link the above mentioned shaders.
5. To compile the project, libglfw.3.3.dylib and libGLEW.2.1.0.dylib are needed
6. If you have questions, please reach out through jiarui.li@mail.concordia.ca
