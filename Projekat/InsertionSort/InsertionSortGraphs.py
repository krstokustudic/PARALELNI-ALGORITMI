import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Učitavanje CSV fajla
df = pd.read_csv("InsertionSortResults.csv", sep=';')

# Postavi stil
sns.set(style="whitegrid")

# 1. Vrijeme izvršavanja
plt.figure()
sns.lineplot(data=df, x="n", y="seq_time", label="Sekvencijalno", marker="o")
sns.lineplot(data=df, x="n", y="par_time", hue="threads", palette="tab10", marker="s", legend="full")
plt.title("Vrijeme izvršavanja Insertion Sort algoritma")
plt.ylabel("Vrijeme (s)")
plt.xlabel("Veličina niza")
plt.legend(title="Broj niti")
plt.tight_layout()
plt.savefig("1_vrijeme_izvrsavanja.png")
plt.show()

# 2. Speedup
plt.figure()
sns.lineplot(data=df, x="n", y="speedup", hue="threads", marker="o")
plt.title("Speedup paralelne verzije Insertion Sort")
plt.ylabel("Speedup")
plt.xlabel("Veličina niza")
plt.axhline(1, linestyle="--", color="gray")
plt.tight_layout()
plt.savefig("2_speedup.png")
plt.show()

# 3. Efikasnost
plt.figure()
sns.lineplot(data=df, x="n", y="efficiency", hue="threads", marker="o")
plt.title("Efikasnost paralelne verzije Insertion Sort")
plt.ylabel("Efikasnost")
plt.xlabel("Veličina niza")
plt.tight_layout()
plt.savefig("3_efikasnost.png")
plt.show()
