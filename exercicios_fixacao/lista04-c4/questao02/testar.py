import unittest
import os


class TestaPoligono(unittest.TestCase):
    def testa_calculo_area(self):
        os.system("./main < testes/teste1.in > testes/teste1.out")
        with open("testes/teste1.out") as file:
            saida = file.read()
            self.assertEqual(saida, "-43.00")


if __name__ == '__main__':
    unittest.main()
