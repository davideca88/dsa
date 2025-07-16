CC = gcc
CFLAGS = -w -O3 -ffast-math
LDFLAGS = -lm
LIBDIR = lib
SRCDIR = src
OUTDIR = out
LIB = $(LIBDIR)/list.o $(LIBDIR)/vector.o $(LIBDIR)/avl_tree.o $(LIBDIR)/binary_tree.o \
      $(LIBDIR)/benchmark.o $(LIBDIR)/hash_table.o $(LIBDIR)/index.o $(LIBDIR)/product.o $(LIBDIR)/graph.o

# Programas
EXES = ex1 ex2 ex3 ex4 ex5 ex6

all: $(LIB) $(EXES)

# Criar diretórios necessários
$(LIBDIR):
	mkdir -p $@

$(OUTDIR):
	mkdir -p $@

# Compilar libs
$(LIBDIR)/%.o: $(SRCDIR)/%.c | $(LIBDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilar executáveis
$(EXES): %: %.c $(LIB)
	$(CC) $(CFLAGS) $(LIB) $< -o $@ $(LDFLAGS)

# Executar um específico
run: | $(OUTDIR)
	@if [ "$(prog)" = "" ]; then \
		echo "Use: make run prog=exN"; \
	else \
		if [ "$(prog)" = "ex6" ]; then \
			./ex6 && mv ex6.txt $(OUTDIR)/ex6.txt && echo "Executado ex6, arquivo movido para $(OUTDIR)/ex6.txt"; \
		else \
			./$(prog) > $(OUTDIR)/$(prog).txt && echo "Executado $(prog), saída em $(OUTDIR)/$(prog).txt"; \
		fi \
	fi

# Executar todos
run-all: $(EXES) | $(OUTDIR)
	@for exe in $(EXES); do \
		if [ "$$exe" = "ex6" ]; then \
			echo "Executando $$exe (gera ex6.txt)"; \
			./$$exe && mv ex6.txt $(OUTDIR)/ex6.txt; \
		else \
			./$$exe > $(OUTDIR)/$$exe.txt && echo "Executado $$exe, saída em $(OUTDIR)/$$exe.txt"; \
		fi; \
	done

# Limpeza
clean:
	rm -f $(EXES) $(LIB) *.bin
	rm -rf $(OUTDIR)