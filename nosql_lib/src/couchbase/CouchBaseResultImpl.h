/**
 *
 *  @file CouchBaseResultImpl.h
 *  An Tao
 *
 *  Copyright 2018, An Tao.  All rights reserved.
 *  https://github.com/an-tao/drogon
 *  Use of this source code is governed by a MIT license
 *  that can be found in the License file.
 *
 *  Drogon
 *
 */
#pragma once
#include <libcouchbase/couchbase.h>
#include <libcouchbase/pktfwd.h>
#include <trantor/utils/NonCopyable.h>
namespace drogon
{
namespace nosql
{
class CouchBaseResultImpl : public trantor::NonCopyable
{
  public:
    virtual ~CouchBaseResultImpl()
    {
    }

  private:
};

class GetLcbResult : public CouchBaseResultImpl
{
  public:
    GetLcbResult(const lcb_RESPGET* resp)
    {
        if (resp->bufh)
        {
            lcb_backbuf_ref((lcb_BACKBUF)resp->bufh);
        }
        else if (resp->nvalue)
        {
            char* tmp = new char[resp->nvalue];
            u_.resp_.value = tmp;
        }
    }
    virtual ~GetLcbResult()
    {
        if (u_.resp_.bufh)
        {
            lcb_backbuf_unref((lcb_BACKBUF)u_.resp_.bufh);
        }
        else if (u_.resp_.value)
        {
            delete[] u_.resp_.value;
        }
    }

  private:
    char* key;
    char* value;
    size_t key_len;
    size_t value_len;
    uint64_t cas;
    uint32_t flags;
};
}  // namespace nosql
}  // namespace drogon