from typing import List
from tqdm import tqdm
import logging

from query.data_object import DataObject
from query.data_query import DataQuery
from query.data_value import DataValue


class QueryBuilder():
    __path_separator = ':'
    __format_separator = '>'

    def __init__(self):
        self.logger = logging.getLogger()

    def build(self, config: dict) -> List[DataObject]:
        data_objects = []
        for key, value in tqdm(
                config.items(),
                desc='Building Queries',
                bar_format="{desc:<70}{percentage:3.0f}% |{bar:70}| {n_fmt:>4}/{total_fmt}"):
            data_object = self.__parse_object(key, value)
            data_objects.append(data_object)
        return data_objects

    def __parse_object(self, name: str, values: dict) -> DataObject:
        required = {'_xpath', '_xref', '_ref'}
        path_value = required & values.keys()
        if len(path_value) != 1:
            error = f'QueryBuilder - DataObject({name}) is missing an anchor. Possible anchors are \'_xpath\', \'_ref\' or \'_xref\''
            self.logger.error(error)
            raise ValueError(error)

        if '_xpath' in path_value:
            xpath = values['_xpath'].split(self.__path_separator)[-1]
            path = DataQuery.XPath(xpath)
        elif '_xref' in path_value:
            xpath = values['_xref'].split(self.__path_separator)[-1]
            path = DataQuery.XPath(xpath, True)
        else:
            ref = values['_ref'].split(self.__path_separator)[-1]
            path = DataQuery.Reference(ref)
        
        data_values = []
        for key, value in values.items():
            if key in required:
                continue

            if isinstance(value, dict):
                data_object = self.__parse_object(key, value)
                data_values.append(data_object)
            else:
                data_value = self.__parse_value(key, value)
                data_values.append(data_value)

        return DataObject(name, path, data_values)

    def __parse_value(self, name: str, value: str) -> DataValue:
        try:
            query = self.__parse_query(value)
            return DataValue(name, query)
        except Exception as e:
            error = f'QueryBuilder - parsing error on query for value \'{name}\': \'{value}\''
            self.logger.error(error, exc_info=e)
            raise ValueError(error) from e

    def __parse_query(self, text: str) -> DataQuery:
        if self.__path_separator not in text:
            path = self.__get_path(text)
            return DataQuery(path)

        raw_value_format, raw_path = text.split(self.__path_separator, 2)
        path = self.__get_path(raw_path)

        if self.__format_separator in raw_value_format:
            raw_value, raw_format = raw_value_format.split(self.__format_separator)
            value = self.__get_value(raw_value)
            format = self.__get_format(raw_format)
        else:
            value = self.__get_value(raw_value_format)
            format = DataQuery.Format.String

        return DataQuery(path, value, format)

    def __get_path(self, path: str) -> DataQuery.XPath:
        illegal_character = [self.__path_separator, self.__format_separator]
        if any(c in illegal_character for c in path):
            error = f'QueryBuilder - illegal characters found on path \'{path}\'. Path must not contain any of the following characters: \':\', \'>\''
            self.logger.error(error)
            raise ValueError(error)

        if path[0] != '&':
            return DataQuery.XPath(path)
        else:
            if path[1] != '(':
                error = f'QueryBuilder - invalid syntax on inline reference \'{path}\'. Inline references must start with \'&(\''
                self.logger.error(error)
                raise ValueError(error)
            return DataQuery.XPath(path, True)

    def __get_value(self, value: str) -> str:
        if (value == '') or (value == 'tag') or (value == 'text'):
            return value
        elif value.startswith('@'):
            if len(value) > 1:
                return value
            else:
                error = f'QueryBuilder - invalid syntax on attribute. Attribute name must be defined'
                self.logger.error(error)
                raise ValueError(error)
        else:
            return 'text'

    def __get_format(self, format: str) -> DataQuery.Format:
        if (format == '') or (format == 'string'):
            return DataQuery.Format.String
        elif (format == 'int'):
            return DataQuery.Format.Integer
        elif (format == 'float'):
            return DataQuery.Format.Float
        elif (format == 'date'):
            return DataQuery.Format.Date
        else:
            return DataQuery.Format.String
