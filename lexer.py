import error


class Lexer:
    def __init__(self, text_to_lex):
        self.token = []
        self.errors = []
        self.text_to_lex = text_to_lex
        self.current_char = ""
        self.pos = 0
        self.line = 0
        self.advance()

    def advance(self):
        self.pos += 1
        self.current_char = self.text_to_lex[self.pos] if self.pos < len(self.text_to_lex) else ""

    def make_name(self):
        name = ""
        while self.current_char in "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789":
            name += self.current_char
            self.advance()
        return name

    def make_number(self):
        num = ""
        while self.current_char in "0123456789":
            num += self.current_char
            self.advance()
        return num

    def make_tokens(self):
        while self.current_char != "":
            if self.current_char in " \t":
                self.advance()
            elif self.current_char == "\n":
                self.line += 1
            elif self.current_char == "+":
                self.token.append({"ADD": "+"})
                self.advance()
            elif self.current_char == "-":
                self.token.append({"SUB": "-"})
                self.advance()
            elif self.current_char == "*":
                self.token.append({"MUL": "*"})
                self.advance()
            elif self.current_char == "/":
                self.token.append({"DIV": "/"})
                self.advance()
            elif self.current_char == "=":
                self.token.append({"EQL": "="})
                self.advance()
            elif self.current_char in "0123456789":
                self.token.append({"INT": self.make_number()})
            elif self.current_char in "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_":
                self.token.append({"NAME": self.make_name()})
            else:
                self.errors.append(error.IllegalCharError(f"{self.current_char} at line {self.line}"))
