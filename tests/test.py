import random
from random import choice
import unittest
import subprocess
from string import ascii_letters


class TestTextMining(unittest.TestCase):
    def test_compileOneWord(self):
        command = "../build/TextMiningCompiler ../words/one_word.txt ../build/words.bin".split()
        popen = subprocess.run(command, capture_output=True)
        self.assertEqual(popen.returncode, 0)

    def test_compileWords(self):
        command = "../build/TextMiningCompiler ../words/words.txt ../build/words.bin".split()
        popen = subprocess.run(command, capture_output=True)
        self.assertEqual(popen.returncode, 0)

    def test_compileMissingArg(self):
        command = "../build/TextMiningCompiler ../words/words.txt".split()
        popen = subprocess.run(command, capture_output=True)
        self.assertEqual(popen.returncode, 1)
        command = "../build/TextMiningCompiler".split()
        popen = subprocess.run(command, capture_output=True)
        self.assertEqual(popen.returncode, 1)

    def test_compileWord(self):
        command = "../build/TextMiningCompiler ../words/words.txt ../build/words.bin".split()
        popen = subprocess.run(command, capture_output=True)
        self.assertEqual(popen.returncode, 0)

    def test_appMissingArg(self):
        command = "../build/TextMiningApp".split()
        popen = subprocess.run(command, capture_output=True)
        self.assertEqual(popen.returncode, 1)

    def test_appOneWord(self):
        approx = "approx 0 n936"
        command = "../build/TextMiningApp ../build/words.bin".split()
        popen = subprocess.run(command, input=approx, capture_output=True, text=True)
        self.assertEqual(popen.stdout, "[{\"word\":\"n936\",\"freq\":705,\"distance\":0}]\n")

    def test_appZeroDistWords(self):
        approx = "\n".join(["approx 0 " + word for word in ["toto", "carotte", "jean", "sylvain", "test"]])
        command = "../build/TextMiningApp ../build/words.bin".split()
        popen = subprocess.run(command, input=approx, capture_output=True, text=True)
        ref = subprocess.run("../ref/osx/TextMiningApp ../ref/osx/words.bin".split(), input=approx, capture_output=True,
                             text=True)
        self.assertEqual(ref.stdout, popen.stdout)

    def test_appRandomWords(self):
        approx = "\n".join(["approx " + str(random.randint(0, 4)) + " " + ''.join(
            choice(ascii_letters) for _ in range(random.randint(4, 10))) for _ in range(10)])
        test = subprocess.run("../build/TextMiningApp ../build/words.bin".split(), input=approx, capture_output=True,
                              text=True)
        ref = subprocess.run("../ref/osx/TextMiningApp ../ref/osx/words.bin".split(), input=approx, capture_output=True,
                             text=True)
        self.assertEqual(ref.stdout, test.stdout)

    """
    def test_appFinal(self):
        with open("out.txt", "r") as f:
            approx = f.read()
        test = subprocess.run("../build/TextMiningApp ../build/words.bin".split(), input=approx, capture_output=True,
                              text=True)
        ref = subprocess.run("../ref/osx/TextMiningApp ../ref/osx/words.bin".split(), input=approx, capture_output=True,
                             text=True)
        self.assertEqual(ref.stdout, test.stdout)
    """

if __name__ == '__main__':
    unittest.main()
