/**
 * conexion.c
 *
 * @file Definiciones relacionadas al encapsulamiento de las conexiones
 * @author Tomás Sánchez
 * @since  04.16.2021
 */

#include "conexion.h"
#include "lib.h"
#include <signal.h>
#include <netdb.h>
#include <fcntl.h>

// ============================================================================================================
//                               ***** Conexion -  Definiciones *****
// ============================================================================================================

/**
 * Buffer de streams.
 *
 * @class
 * @private
 */
typedef struct Buffer
{
	// El tamaño del Buffer
	int size;
	// The stream itself
	void *stream;
} buffer_t;

/**
 * Paquete a enviable en conexiones.
 *
 * @class
 * @private
 */
typedef struct Paquete
{
	// Código de operación
	opcode_t opcode;
	// Buffer interno
	buffer_t *buffer;
} paquete_t;

// ============================================================================================================
//                               ***** Funciones Privadas - Declaraciones *****
// ============================================================================================================

/**
 * Instancia un paquete.
 *
 * @private
 * @param opcode el código de operacion
 * @param stream el stream a enviarse
 * @returns un nuevo paquete, listo a serializarse
 */
static paquete_t *paquete_create(opcode_t, char *);

/**
 * Libera memoria de un paquete
 *
 * @private
 * @param paquete el paquete a borrarse
 */
static void paquete_destroy(paquete_t *);

/**
 * Ordena los bytes de un paquete.
 *
 * @private
 * @param paquete el paquete a serializarse
 * @returns un paquete listo para enviarse
 */
static void *paquete_serializar(paquete_t *is_paquete);

/**
 * Calcula la cantidad de bytes que necesita un paquete.
 *
 * @private
 * @param paquete el mismísimo paquete
 * @returns los bytes que requiere
 */
static int paquete_calcular_bytes(paquete_t *);

/**
 * Instancia un buffer.
 *
 * @private
 * @param size el tamaño que requiere el buffer
 * @returns un nuevo buffer
 */
static buffer_t *buffer_create(size_t);

/**
 * Libera la memoria de un buffer
 *
 * @private
 * @param buffer el buffer a destruirse.
 */
static void buffer_destroy(buffer_t *);

/**
 * Encapsula los funcionamientos de getaddrinfo
 *
 * @param ip el ip a conectarse
 * @param puerto el puerto de conexión
 * @param conexion la referencia de la conexion a direccionar
 */
int direccionar(char *, char *, conexion_t *);

// ============================================================================================================
//                               ***** Funciones Privadas - Definiciones *****
// ============================================================================================================

// -----------------------------------------------------------
//  Paquete
// ------------------------------------------------------------

static paquete_t *
paquete_create(opcode_t iv_opcode, char *iv_stream)
{
	// Estructura a Exportar paquete - el nuevo paquete a serializarse
	paquete_t *es_paquete = malloc(sizeof(paquete_t));

	// Variable Local size - longitud de palabra + '\0'
	size_t lv_buffer_size = strlen(iv_stream) + 1;

	es_paquete->opcode = iv_opcode;
	es_paquete->buffer = buffer_create(lv_buffer_size);

	// Copio los bytes del stream al buffer
	memcpy(es_paquete->buffer->stream, iv_stream, es_paquete->buffer->size);

	return es_paquete;
}

static paquete_t *
paquete_stream_create(opcode_t iv_opcode, void *iv_stream, ssize_t stream_size)
{
	// Estructura a Exportar paquete - el nuevo paquete a serializarse
	paquete_t *es_paquete = malloc(sizeof(paquete_t));

	es_paquete->opcode = iv_opcode;
	es_paquete->buffer = buffer_create(stream_size);

	// Copio los bytes del stream al buffer
	memcpy(es_paquete->buffer->stream, iv_stream, es_paquete->buffer->size);

	return es_paquete;
}

static inline void paquete_destroy(paquete_t *is_paquete)
{
	buffer_destroy(is_paquete->buffer);
	free(is_paquete);
}

static void *paquete_serializar(paquete_t *is_paquete)
{
	// Variable Local bytes - the bytes a enviarse
	int lv_bytes = paquete_calcular_bytes(is_paquete);

	// Exporting paquete - el paquete serializado
	void *e_paquete = NULL;
	e_paquete = malloc(lv_bytes);

	// Variable Local offset - el offset del stream
	int lv_offset = 0;

	// Copio de a bytes, incrementando el offset en todos los casos
	/**
	 *          [ OPCODE ][ SIZE del MSG ][ MSG ]
	 */
	memcpy(e_paquete + lv_offset, &(is_paquete->opcode), sizeof(int));
	lv_offset += sizeof(int);

	memcpy(e_paquete + lv_offset, &(is_paquete->buffer->size), sizeof(int));
	lv_offset += sizeof(int);

	memcpy(e_paquete + lv_offset, is_paquete->buffer->stream, is_paquete->buffer->size);
	lv_offset += is_paquete->buffer->size;

	return e_paquete;
}

static int paquete_calcular_bytes(paquete_t *is_paquete)
{
	// Bytes del buffer + bytes del opcode + el 'size' de los bytes (cantidad de bytes enviados es un int)
	return is_paquete->buffer->size + 2 * sizeof(int);
}

// -----------------------------------------------------------
//  Buffer
// ------------------------------------------------------------

static buffer_t *buffer_create(size_t iv_size)
{
	// Estructura a Exportar buffer - el nuevo buffer de tamaño IV_SIZE
	buffer_t *es_buffer = malloc(sizeof(buffer_t));
	es_buffer->size = iv_size;
	es_buffer->stream = malloc(es_buffer->size);
	return es_buffer;
}

static inline void buffer_destroy(buffer_t *is_buffer)
{
	free(is_buffer->stream);
	free(is_buffer);
}

// -----------------------------------------------------------
//  Misc
// ------------------------------------------------------------

int direccionar(char *iv_ip, char *iv_puerto, conexion_t *is_conexion)
{
	// Estructura local hints - Las hints para la creacion del socket.
	struct addrinfo ls_hints;
	int rv;

	// Seteos de memoria a las hints -- No importa como funciona
	memset(&ls_hints, 0, sizeof(ls_hints));
	ls_hints.ai_family = AF_UNSPEC;
	ls_hints.ai_socktype = SOCK_STREAM;
	ls_hints.ai_flags = AI_PASSIVE;
	if ((rv = getaddrinfo(iv_ip, iv_puerto, &ls_hints, &is_conexion->info_server)) != 0)
	{
		fprintf(stderr, "%s\n", gai_strerror(rv));
		return ERROR;
	}

	return SUCCESS;
}

// -----------------------------------------------------------
//  Streams
// ------------------------------------------------------------

bool tiene_mensaje(char *iv_mensaje)
{
	return iv_mensaje != NULL && strlen(iv_mensaje) > 0;
}

ssize_t enviar_str(char *iv_str, int iv_socket)
{
	// Estructura Local paquete - el paquete a enviar
	paquete_t *ls_paquete = paquete_create(MSG, iv_str);

	// Local stream - el paquete serializado, requiere free(1)
	void *l_stream = paquete_serializar(ls_paquete);

	// Variable a Exportar bytes - Los bytes enviados o ERROR (-1)
	ssize_t ev_bytes = send(iv_socket, l_stream, paquete_calcular_bytes(ls_paquete), 0);

	free(l_stream);

	paquete_destroy(ls_paquete);

	return ev_bytes;
}

ssize_t enviar_stream(opcode_t opcode, void *iv_str, size_t iv_str_size, int iv_socket)
{
	// Estructura Local paquete - el paquete a enviar
	paquete_t *ls_paquete = paquete_stream_create(opcode, iv_str, iv_str_size);

	// Local stream - el paquete serializado, requiere free(1)
	void *l_stream = paquete_serializar(ls_paquete);

	// Variable a Exportar bytes - Los bytes enviados o ERROR (-1)
	ssize_t ev_bytes = send(iv_socket, l_stream, paquete_calcular_bytes(ls_paquete), 0);

	free(l_stream);

	paquete_destroy(ls_paquete);

	return ev_bytes;
}

// ============================================================================================================
//                               ***** Funciones Públicas, Definiciones *****
// ============================================================================================================

// ------------------------------------------------------------
//  Constructor y Destructor
// ------------------------------------------------------------

conexion_t conexion_cliente_create(char *iv_ip, char *iv_puerto)
{
	// Estructura a Exportar conexion - La nueva conexión
	conexion_t es_conexion;

	direccionar(iv_ip, iv_puerto, &es_conexion);

	// Creo el socket y la conexion
	es_conexion.socket = socket(es_conexion.info_server->ai_family, es_conexion.info_server->ai_socktype, es_conexion.info_server->ai_protocol);
	es_conexion.conectado = false;

	return es_conexion;
}

conexion_t conexion_servidor_create(char *iv_ip, char *iv_puerto)
{

	// Estructura a Exportar conexion - La nueva conexión
	conexion_t es_conexion = {NULL, 0, false};
	int yes = 1;

	if (direccionar(iv_ip, iv_puerto, &es_conexion) == ERROR)
	{
		return es_conexion;
	}

	// Estructura local info - iterador de la lista de ardrinfo.
	struct addrinfo *ls_info;

	for (ls_info = es_conexion.info_server; ls_info != NULL; ls_info = ls_info->ai_next)
	{
		// Busco el socket que puede abirse
		es_conexion.socket = socket(ls_info->ai_family, ls_info->ai_socktype, ls_info->ai_protocol);
		if (es_conexion.socket < 0)
		{
			continue;
		}

		// Lose the pesky "address already in use" error message
		setsockopt(es_conexion.socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

		// Avoids a blocking accept state (ADDS BUSY WAITING)
		// fcntl(es_conexion.socket, F_SETFL, O_NONBLOCK);

		// Corroboro que además de abrirse, el socket puede bindears
		if (bind(es_conexion.socket, ls_info->ai_addr, ls_info->ai_addrlen) EQ ERROR)
		{
			// Si no bindea, cierro el socket
			close(es_conexion.socket);
			continue;
		}

		// Si todo salio OK simplemente rompo el LOOP.
		break;
	}

	// Para el SERVER, considero conectado cuando se encuentra escuchando (listen)
	es_conexion.conectado = false;

	return es_conexion;
}

inline void conexion_destroy(conexion_t *is_conexion)
{
	conexion_desconectar(is_conexion);
	// Libero la información del server
	freeaddrinfo(is_conexion->info_server);
}

// ------------------------------------------------------------
//  Conexión Intrínseca
// ------------------------------------------------------------

inline int conexion_conectar(conexion_t *is_conexion)
{
	// Conecto, y guardo si se pudo conectar
	is_conexion->conectado =
		connect(is_conexion->socket, is_conexion->info_server->ai_addr, is_conexion->info_server->ai_addrlen) != ERROR;

	// Devuelvo si tuvo exito o error
	return is_conexion->conectado ? is_conexion->socket : ERROR;
}

inline int conexion_escuchar(conexion_t *is_conexion)
{
	// Escucho, y guardo el resultado de si se pudo abrir la escucha

	is_conexion->conectado = listen(is_conexion->socket, SOMAXCONN) != ERROR;

	return is_conexion->conectado ? SUCCESS : ERROR;
}

inline int conexion_desconectar(const conexion_t *is_conexion)
{
	return close(is_conexion->socket);
}

int conexion_esperar_cliente(conexion_t is_conexion)
{
	// Estructura Local direccion de cliente - La informacion de direccion del cliente.
	struct sockaddr_in ls_dir_cliente;
	// Variable local tamaño de dirección
	unsigned int lv_dir_size = sizeof(struct sockaddr_in);

	return accept(is_conexion.socket, (void *)&ls_dir_cliente, &lv_dir_size);
}

inline bool conexion_esta_conectada(conexion_t is_conexion)
{
	return is_conexion.conectado;
}

// ------------------------------------------------------------
//  Comunicación
// ------------------------------------------------------------

// --------------
//  Mensajes
// --------------

inline ssize_t conexion_enviar_mensaje(conexion_t is_conexion, char *iv_mensaje)
{
	return conexion_esta_conectada(is_conexion) ? enviar_str(iv_mensaje, is_conexion.socket) : ERROR;
}

// --------------
//  Mensajes
// --------------
inline ssize_t conexion_enviar_stream(conexion_t is_conexion, opcode_t opcode, void *iv_stream, size_t iv_size)
{
	return conexion_esta_conectada(is_conexion) ? enviar_stream(opcode, iv_stream, iv_size, is_conexion.socket) : ERROR;
}
