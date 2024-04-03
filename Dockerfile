FROM gcc:12.3-bookworm
LABEL authors="AminBidad1 Amin4424 Amirrez4 afakhari"

WORKDIR /code/
# copy codes
COPY . /code

# install dependencies
RUN apt-get install make

# build the project
RUN chmod +x main.sh
RUN ./main.sh

# Run the project
CMD ./main
