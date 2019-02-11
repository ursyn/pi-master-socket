# in_master.indp
Plik input dla drivera

I wiersz: architektura 0 - linux, 1 - solaris26

II wiersz: num_executables

III wiersz: exec, j

__IV wiersz: job_size - całkowita liczba iteracji przy generacji pi__

__V wiersz: num_tasks - liczba zadań pomiędzy które zostanie rozdzielone job_size__


Czasami tworzy się plik checkpoint, który na razie (dla bazowego przypadku) należy usunąć przed odpaleniem programu

Liczba węzłów to Machine_count? w pliku submit_***
