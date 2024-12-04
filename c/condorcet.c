/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/09/05 14:15:32 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Python.h>
#include "condorcet_core.h"

static PyObject *find_winner(PyObject *self, PyObject *args) {
    PyObject *rankings;
    int num_candidates, num_voters;

    if (!PyArg_ParseTuple(args, "Oii", &rankings, &num_voters, &num_candidates)) {
        return NULL;
    }

    int ranks[MAX_CANDIDATES][MAX_CANDIDATES];
    int matrix[MAX_CANDIDATES][MAX_CANDIDATES] = {0};

    // Convert Python list to C array
    for (int v = 0; v < num_voters; v++) {
        PyObject *row = PyList_GetItem(rankings, v);
        for (int c = 0; c < num_candidates; c++) {
            ranks[v][c] = (int)PyLong_AsLong(PyList_GetItem(row, c));
        }
    }

    // Calculate pairwise matrix and find winner
    calculate_pairwise_matrix(ranks, num_voters, num_candidates, matrix);
    int winner = find_condorcet_winner(matrix, num_candidates);

    return PyLong_FromLong(winner);
}

static PyMethodDef CondorcetMethods[] = {
    {"find_winner", find_winner, METH_VARARGS, "Find the Condorcet winner."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef condorcetmodule = {
    PyModuleDef_HEAD_INIT,
    "condorcet",
    NULL,
    -1,
    CondorcetMethods
};

PyMODINIT_FUNC PyInit_condorcet(void) {
    return PyModule_Create(&condorcetmodule);
}

